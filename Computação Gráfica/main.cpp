#include <stdio.h>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <functional>
#include "grayscale.h"
#include "coloured.h"
#include "improc.h"
#include "defs.h"
#include "algorithms.h"
#include "kernel.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    cv::Mat image = improc::grayscale::singleChannel(cv::imread(argv[1], 1));

    // Kernel z = Kernel::laplacian(true);
    // double summm = 0;
    // for (int i = 0; i < z.rows(); i++) {
    //     for (int j = 0; j < z.columns(); j++) {
    //         std::cout << std::round(z.get(i, j) * 255) << " ";
    //         summm += z.get(i, j);
    //     }

    //     std::cout << "\n";
    // }

    // std::cout << summm << "\n";
    // return 0;




    // double score = 0;
    // cv::Mat greenScore = improc::overrideColor<cv::Vec3b>(image, [&](const cv::Vec3b& pixel) {
    //     int green = pixel[1];
    //     int notGreen = (pixel[0] + pixel[2]) / 2;
    //     int val = std::max(0, green);

    //     int scaledVal = val;

    //     score += (scaledVal * (100.0 / 255.0));

    //     return cv::Vec3b(scaledVal, scaledVal, scaledVal);
    // });

    // std::cout << score / (image.rows * image.cols) << "\n";

    // cv::Mat greenScore = improc::coloured::isolateChannel(image, 1);

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    // int optimalThreshold = algorithms::otsu(image);

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    cv::imshow("Original", image);
    // cv::imshow("Mean", improc::grayscale::boxBlur(image, 7));
    // cv::imshow("Median", improc::grayscale::median(image, 4));
    // cv::imshow("Gaussian", improc::grayscale::gaussianBlur(image, 7, 2));
    cv::imshow("Laplacian", improc::grayscale::detectEdges(image, true, 128));
    cv::imshow("Sharpened", improc::grayscale::sharpen(image, true));
    cv::imshow("Unsharp Masked", improc::grayscale::unsharpMask(image, Kernel::gaussian(7, 3)));
    // for (int i = 0; i < 256; i++) {
    //     cv::imshow("Threshold", improc::grayscale::threshold(image, i));
    //     cv::waitKey(10);
    // }
    // cv::imshow("Red", improc::isolateChannel(image, 2));
    // cv::imshow("Green", improc::isolateChannel(image, 1));
    // cv::imshow("Blue", improc::isolateChannel(image, 0));

    std::vector<double> histogram = improc::grayscale::histogram(image);

    // double sum = 0;
    // for (int i = 0; i < histogram.size(); i++) {
    //     std::cout << i << " => " << histogram[i] << "\n";
    //     sum += histogram[i];
    // }

    // std::cout << "Sum = " << sum << "\n";

    cv::imshow("histogram", improc::visualizeHistogram(histogram));
    //cv::imshow("otsu", improc::grayscale::threshold(image, optimalThreshold));
    // cv::imshow("pow", improc::grayscale::power(image, 5));
    // cv::imshow("piecewise", improc::grayscale::piecewiseLinearTransform(image, 50, 10, 200, 230));

    cv::waitKey(0);
    return 0;

}
