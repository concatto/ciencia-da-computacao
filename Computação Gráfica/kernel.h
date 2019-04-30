#ifndef KERNEL_H
#define KERNEL_H

#include <vector>
#include <cassert>
#include "defs.h"
#include <cmath>

class Kernel {
private:
  int rowCount;
  int columnCount;
  Matrix<double> data;

public:
  Kernel(int rowCount, int columnCount) : rowCount(rowCount), columnCount(columnCount) {
    assert(rowCount % 2 != 0 && "rowCount must be odd");
    assert(columnCount % 2 != 0 && "columnCount must be odd");

    data.resize(rowCount);
    for (std::vector<double>& row : data) {
      row.resize(columnCount);
    }
  }

  int rows() const {
    return rowCount;
  }

  int columns() const {
    return columnCount;
  }

  void set(int row, int column, double value) {
    data[row][column] = value;
  }

  double get(int row, int column) const {
    return data[row][column];
  }

  int rowOffset() const {
    return rowCount / 2;
  }

  int columnOffset() const {
    return columnCount / 2;
  }

  void multiply(double value) {
    for (int i = 0; i < rowCount; i++) {
      for (int j = 0; j < columnCount; j++) {
        set(i, j, get(i, j) * value);
      }
    }
  }

  static Kernel square(int size, double value) {
    Kernel kernel(size, size);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        kernel.set(i, j, value);
      }
    }

    return kernel;
  }

  static Kernel gaussian(int size, double sigma) {
    Kernel kernel(size, size);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        double x = i - kernel.rowOffset();
        double y = j - kernel.columnOffset();

        double normalization = 1 / (2 * PI * std::pow(sigma, 2));
        double term = std::exp(-((x * x) + (y * y)) / (2 * std::pow(sigma, 2)));

        kernel.set(i, j, normalization * term);
      }
    }

    return kernel;
  }

  static Kernel laplacian(bool withCorners) {
    Kernel kernel = square(3, 1);

    if (withCorners) {
      kernel.set(1, 1, -8);
    } else {
      kernel.set(0, 0, 0);
      kernel.set(0, 2, 0);
      kernel.set(2, 0, 0);
      kernel.set(2, 2, 0);
      kernel.set(1, 1, -4);
    }

    kernel.multiply(-1);
    return kernel;
  }
};

#endif