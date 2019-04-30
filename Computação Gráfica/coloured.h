#ifndef COLOURED_H
#define COLOURED_H

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
#include "improc.h"

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


#endif