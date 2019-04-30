#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <functional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <opencv2/opencv.hpp>
#include "defs.h"
#include "utils.h"
#include "piecewise.h"
#include "kernel.h"
#include "coloured.h"

namespace improc::grayscale {
    using Pixel = ubyte;
    using ConvPair = std::pair<Pixel, double>;

    cv::Mat singleChannel(const cv::Mat& image) {
        cv::Mat dst = image.clone();

        cv::cvtColor(image, dst, cv::COLOR_BGR2GRAY);

        return dst;
    }

    cv::Mat brightnessGrayscale(const cv::Mat& image) {
        return singleChannel(improc::coloured::multiChannelGrayscale(image, 0.07 * 3, 0.72 * 3, 0.21 * 3));
    }

    cv::Mat threshold(const cv::Mat& image, int value) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return pixel < value ? 0 : 255;
        });
    }

    cv::Mat negative(const cv::Mat& image) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return 255 - pixel;
        });
    }

    cv::Mat windowing(const cv::Mat& image, int first, int second) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            int newValue;

            if (pixel < first) {
                newValue = 0;
            } else if (pixel > second) {
                newValue = 255;
            } else {
                double delta = second - first;
                newValue = std::round(lerp(normalize(pixel, first, second), 0, 255));
            }

            return static_cast<Pixel>(newValue);
        });
    }

    std::vector<double> histogram(const cv::Mat& image) {
        std::vector<double> intensities(256, 0);

        forEachPixel<Pixel>(image, [&](const Pixel& pixel) {
            intensities[pixel]++;
        });

        for (double& count : intensities) {
            count /= static_cast<double>(image.rows * image.cols);
        }

        return intensities;
    }

    cv::Mat autoWindowing(const cv::Mat& image) {
        std::vector<double> imageHistogram = histogram(image);

        auto isNotZero = [&](double x) { return x > 0; };
        auto firstIt = std::find_if(imageHistogram.begin(), imageHistogram.end(), isNotZero);
        auto lastIt = std::find_if(imageHistogram.rbegin(), imageHistogram.rend(), isNotZero);

        int first = std::distance(imageHistogram.begin(), firstIt);
        int last = std::distance(lastIt, imageHistogram.rend());

        std::cout << "First nonzero at " << first << ". Last nonzero at " << last << "\n";

        return windowing(image, first, last);
    }

    cv::Mat logarithm(const cv::Mat& image) {
        double c = 255.0 / std::log(256.0);

        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return c * std::log(1 + pixel);
        });
    }

    cv::Mat power(const cv::Mat& image, double gamma) {
        double c = 255.0 / std::pow(255, gamma);

        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return c * std::pow(pixel, gamma);
        });
    }

    cv::Mat piecewiseLinearTransform(const cv::Mat& image, int x1, int y1, int x2, int y2) {
        PiecewiseLinearFunction func({
            {0, 0},
            {x1, y1}, 
            {x2, y2}, 
            {255, 255}
        });

        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return func.apply(pixel);
        });
    }

    cv::Mat convolveMapping(const cv::Mat& image, const Kernel& kernel, std::function<Pixel(const std::vector<ConvPair>&)> mapper) {
        cv::Mat clone = image.clone();

        for (int i = 0; i < clone.rows; i++) {
            for (int j = 0; j < clone.cols; j++) {
                std::vector<ConvPair> pairs;

                for (int a = 0; a < kernel.rows(); a++) {
                    for (int b = 0; b < kernel.columns(); b++) {
                        int row = i + a - kernel.rowOffset();
                        int col = j + b - kernel.columnOffset();

                        row = constrain(row, 0, clone.rows);
                        col = constrain(col, 0, clone.cols);

                        // std::cout << a << ", " << b << "\n";
                        pairs.push_back({ image.at<Pixel>(row, col), kernel.get(a, b) });
                    }
                }

                clone.at<Pixel>(i, j) = constrain(mapper(pairs), 0, 255);
            }
        }

        return clone;
    }

    cv::Mat convolve(const cv::Mat& image, const Kernel& kernel) {
        return convolveMapping(image, kernel, [&](const std::vector<ConvPair>& pairs) {
            double sum = 0;
            double weightSum = 0;

            for (const ConvPair& pair : pairs) {
                sum += pair.first * pair.second;
                weightSum += pair.second;
            }

            return static_cast<Pixel>(constrain(std::round(sum / weightSum), 0, 255));
        });
    }

    cv::Mat boxBlur(const cv::Mat& image, int size) {
        return convolve(image, Kernel::square(size, 1));
    }

    cv::Mat gaussianBlur(const cv::Mat& image, int size, double sigma) {
        return convolve(image, Kernel::gaussian(size, sigma));
    }

    cv::Mat median(const cv::Mat& image, int size) {
        return convolveMapping(image, Kernel::square(size, 0), [&](std::vector<ConvPair> pairs) {
            std::sort(pairs.begin(), pairs.end(), [&](const ConvPair& a, const ConvPair& b) {
                return a.first < b.first;
            });

            int middle = pairs.size() / 2;

            return pairs[middle].first;
        });
    }

    cv::Mat detectEdges(const cv::Mat& image, bool withCorners, int correction = 0) {
        Kernel kernel = Kernel::laplacian(withCorners);

        return convolveMapping(image, kernel, [&](const std::vector<ConvPair>& pairs) {
            double sum = 0;

            for (const ConvPair& pair : pairs) {
                int pixelValue = static_cast<int>(pair.first);
                sum += pixelValue * pair.second;
            }

            return static_cast<Pixel>(constrain(std::round(sum) + correction, 0, 255));
        });
    }

    cv::Mat sharpen(const cv::Mat& image, bool withCorners, int correction = 0) {
        cv::Mat edges = detectEdges(image, withCorners, correction);

        return improc::merge<Pixel>(image, edges, [&](int a, int b) {
            int sum = a + b;
            
            return static_cast<Pixel>(constrain(sum - correction, 0, 255));
        });
    }

    cv::Mat unsharpMask(const cv::Mat& image, const Kernel& kernel) {
      cv::Mat smooth = convolve(image, kernel);

      cv::Mat edges = improc::merge<Pixel>(image, smooth, [&](int a, int b) {
        return constrain(a - b  + 128, 0, 255);
      });

      return improc::merge<Pixel>(image, edges, [&](int a, int b) {
        return constrain(a + b - 128, 0, 255);
      });
    }
}

#endif