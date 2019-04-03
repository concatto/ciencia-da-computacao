#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <functional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <opencv2/opencv.hpp>
#include "defs.h"
#include "utils.h"
#include "piecewise.h"

namespace improc {
    template <class PixelType>
    cv::Mat overrideColor(const cv::Mat& image, const Mapper<PixelType>& mapper) {
        cv::Mat clone = image.clone();

        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                PixelType pixel = image.at<PixelType>(i, j);

                clone.at<PixelType>(i, j) = mapper(pixel);
            }
        }

        return clone;
    }

    template <class PixelType>
    void forEachPixel(const cv::Mat& image, const Consumer<PixelType>& consumer) {
        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                consumer(image.at<PixelType>(i, j));
            }
        }
    }

    cv::Mat visualizeHistogram(const std::vector<double>& histogram) {
        cv::Mat viz(histogram.size(), histogram.size(), CV_8U, 255);

        double max = *std::max_element(histogram.begin(), histogram.end());
        double coefficient = 0.9 / max;

        for (int i = 0; i < histogram.size(); i++) {
            double value = histogram[i];
            int height = std::round(value * viz.rows * coefficient);

            for (int j = 0; j < height; j++) {
                int yPos = viz.rows - j - 1;

                viz.at<ubyte>(yPos, i) = 0;
            }
        }

        return viz;
    }

    cv::Mat visualizeHistogram(const std::vector<double>& histogram, int highlight) {
        cv::Mat viz = visualizeHistogram(histogram);

        for (int i = 0; i < histogram.size(); i++) {
            viz.at<ubyte>(i, highlight) = 0;
        }

        return viz;
    }
}


namespace improc::coloured {
    using Pixel = cv::Vec3b;

    cv::Mat multiChannelGrayscale(const cv::Mat& image, double bWeight = 1, double gWeight = 1, double rWeight = 1) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            double color = (
                pixel[0] * bWeight +
                pixel[1] * gWeight +
                pixel[2] * rWeight
            ) / 3;
            
            return Pixel(color, color, color);
        });
    }

    cv::Mat isolateChannel(const cv::Mat& image, int channelIndex) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            double color = pixel[channelIndex];
            
            return Pixel(color, color, color);
        });
    }

    cv::Mat threshold(const cv::Mat& image, int value) {
        Mapper<ubyte> mapper = [&](int x) {
            return x < value ? 0 : 255;
        };

        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            int blue = mapper(pixel[0]);
            int green = mapper(pixel[1]);
            int red = mapper(pixel[2]);
            
            return Pixel(blue, green, red);
        });
    }

    cv::Mat negative(const cv::Mat& image) {
        return overrideColor<Pixel>(image, [&](const Pixel& pixel) {
            return Pixel(
                255 - pixel[0],
                255 - pixel[1],
                255 - pixel[2]
            );
        });
    }

    cv::Mat brightnessGrayscale(const cv::Mat& image) {
        return multiChannelGrayscale(image, 0.07 * 3, 0.72 * 3, 0.21 * 3);
    }
}


namespace improc::grayscale {
    using Pixel = ubyte;

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
}

#endif