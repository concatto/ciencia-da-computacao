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

    cv::Mat image = improc::brightnessGrayscale(cv::imread(argv[1], 1));

    if (!image.data) {
        printf("No image data \n");
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);


    cv::imshow("Original", improc::threshold(image, 100));
    cv::imshow("Red", improc::isolateChannel(image, 2));
    cv::imshow("Green", improc::isolateChannel(image, 1));
    cv::imshow("Blue", improc::isolateChannel(image, 0));

    cv::waitKey(0);
    return 0;

}
