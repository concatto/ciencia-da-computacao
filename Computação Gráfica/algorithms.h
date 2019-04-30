#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include "grayscale.h"
#include "utils.h"

namespace algorithms {
  int otsu(const cv::Mat& image) {
    std::vector<double> histogram = improc::grayscale::histogram(image);

    std::function<double(int)> retrieveProbability = [&](const int& i) { return histogram[i]; };
    //histogram = std::vector<double>(20);


    double bestLoss = std::numeric_limits<double>::max();
    int bestThreshold = 0;


    for (int i = 1; i < histogram.size(); i++) {
      std::vector<int> left = sequence(0, i);
      std::vector<int> right = sequence(i, histogram.size());

      std::vector<double> probLeft = mapVector<int, double>(left, retrieveProbability);
      std::vector<double> probRight = mapVector<int, double>(right, retrieveProbability);

      double wLeft = vectorSum(probLeft);
      double wRight = vectorSum(probRight);

      double loss = wLeft * variance(probLeft, left) + wRight * variance(probRight, right);

      if (loss < bestLoss) {
        bestLoss = loss;
        bestThreshold = i;
      }
    }

    return bestThreshold;
  }

}

#endif