#include <functional>
#include <opencv2/opencv.hpp>
#include "defs.h"

namespace improc {
    cv::Mat overrideColor(const cv::Mat& image, const Mapper<cv::Vec3b>& mapper) {
        cv::Mat clone = image.clone();

        for (int i = 0; i < image.rows; i++) {
            for (int j = 0; j < image.cols; j++) {
                cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);

                clone.at<cv::Vec3b>(i, j) = mapper(pixel);
            }
        }

        return clone;
    }

    cv::Mat grayscale(const cv::Mat& image, double bWeight = 1, double gWeight = 1, double rWeight = 1) {
        return overrideColor(image, [&](const cv::Vec3b& pixel) {
            double color = (
                pixel[0] * bWeight +
                pixel[1] * gWeight +
                pixel[2] * rWeight
            ) / 3;
            
            return cv::Vec3b(color, color, color);
        });
    }

    cv::Mat brightnessGrayscale(const cv::Mat& image) {
        return improc::grayscale(image, 0.07 * 3, 0.72 * 3, 0.21 * 3);
    }

    cv::Mat isolateChannel(const cv::Mat& image, int channelIndex) {
        return overrideColor(image, [&](const cv::Vec3b& pixel) {
            double color = pixel[channelIndex];
            
            return cv::Vec3b(color, color, color);
        });
    }

    cv::Mat negative(const cv::Mat& image) {
        return overrideColor(image, [&](const cv::Vec3b& pixel) {
            return cv::Vec3b(
                255 - pixel[0],
                255 - pixel[1],
                255 - pixel[2]
            );
        });
    }

    cv::Mat threshold(const cv::Mat& image, int value) {
        Mapper<ubyte> mapper = [&](int x) {
            return x < value ? 0 : 255;
        };

        return overrideColor(image, [&](const cv::Vec3b& pixel) {
            int blue = mapper(pixel[0]);
            int green = mapper(pixel[1]);
            int red = mapper(pixel[2]);
            
            return cv::Vec3b(blue, green, red);
        });
    }
}