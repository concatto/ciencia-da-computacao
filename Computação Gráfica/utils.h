#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

double lerp(double alpha, double a, double b) {
    double r = b * alpha + a * (1 - alpha);
    //std::cout << "Alpha = " << alpha << ". Scaled = " << r << "\n";
    return r;
}

double normalize(double x, double lower, double upper) {    
    return (x - lower) / static_cast<double>(upper - lower);
}

template <class T>
T vectorSum(const std::vector<T>& vector) {
  return std::accumulate(vector.begin(), vector.end(), static_cast<T>(0));
}

template <class T>
double weightedAverage(const std::vector<double>& weights, const std::vector<T>& values) {
  double weightSum = vectorSum(weights);

  double numerator = 0;
  for (int i = 0; i < weights.size(); i++) {
    numerator += weights[i] * values[i];
  }

  return numerator / weightSum;
}

template <class T>
double variance(const std::vector<double>& probabilities, const std::vector<T>& values) {
  double mean = weightedAverage(probabilities, values);

  double sum = 0;
  for (int i = 0; i < probabilities.size(); i++) {
    sum += probabilities[i] * std::pow(values[i] - mean, 2);
  }

  return sum;
}

std::vector<int> sequence(int fromInclusive, int toExclusive) {
  std::vector<int> values(toExclusive - fromInclusive);
  std::iota(values.begin(), values.end(), fromInclusive);

  return values;
}

template <class T>
void writeContainer(const T& container, std::ostream& out = std::cout) {
  out << "[";
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (it != container.begin()) {
      out << ", ";
    }

    out << *it;
  }
  out << "]\n";
}

template <class T, class U>
std::vector<U> mapVector(const std::vector<T>& container, std::function<U(const T&)> mapper) {
  std::vector<U> output;
  std::transform(container.begin(), container.end(), std::back_inserter(output), mapper);

  return output;
}

#endif