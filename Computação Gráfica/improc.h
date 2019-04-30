#ifndef IMPROC_H
#define IMPROC_H

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

    template <class PixelType, class Consumer>
    cv::Mat merge(const cv::Mat& lhs, const cv::Mat& rhs, const Consumer& consumer) {
        cv::Mat result = lhs.clone();

        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                PixelType lhsVal = lhs.at<PixelType>(i, j);
                PixelType rhsVal = rhs.at<PixelType>(i, j);

                result.at<PixelType>(i, j) = static_cast<PixelType>(consumer(lhsVal, rhsVal));
            }
        }

        return result;
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

#endif