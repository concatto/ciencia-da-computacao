#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <functional>
#include "functions.h"
#include "defs.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    cv::Mat image = improc::grayscale::singleChannel(cv::imread(argv[1], 1));

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);


    cv::imshow("Original", image);
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
    cv::imshow("pow", improc::grayscale::power(image, 5));
    cv::imshow("piecewise", improc::grayscale::piecewiseLinearTransform(image, 50, 10, 200, 230));

    cv::waitKey(0);
    return 0;

}
