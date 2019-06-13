#ifndef MATRIX_H_
#define MATRIX_H_

#include <cassert>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace math {

template<typename ValueType, size_t Rows, size_t Cols>
class Matrix {
 public:
  typedef ValueType Scalar;

 public:
  Matrix() {
    rows_ = Rows;
    cols_ = Cols;
  }

  Matrix(const Matrix& other) {
    memcpy(data_, other.data_, sizeof(data_));
  }

  ~Matrix() = default;

  // return the number of rows
  inline size_t RowSize() const {
    return rows_;
  }

  // return the number of columns
  inline size_t ColSize() const {
    return cols_;
  }

  // return the number of elements
  inline size_t Size() const {
    return rows_ * cols_;
  }

  inline Matrix& operator=(const Matrix& other) {
    assert(rows_ == other.rows_);
    assert(cols_ == other.cols_);
    if (this != &other) {
      memcpy(data_, other.data_, sizeof(data_));
    }
    return (*this);
  }

  inline Matrix operator+(const Matrix& other) const {
    assert(rows_ == other.rows_);
    assert(cols_ == other.cols_);
    Matrix<Scalar, Rows, Cols> res;
    for (size_t row = 0; row < res.rows_; ++row) {
      for (size_t col = 0; col < res.cols_; ++col) {
        res(row, col) = data_[row][col] + other(row, col);
      }
    }
    return res;
  }

  inline Matrix operator-(const Matrix& other) const {
    assert(rows_ == other.rows_);
    assert(cols_ == other.cols_);
    Matrix<Scalar, Rows, Cols> res;
    for (size_t row = 0; row < res.rows_; ++row) {
      for (size_t col = 0; col < res.cols_; ++col) {
        res(row, col) = data_[row][col] - other(row, col);
      }
    }
    return res;
  }

  inline Matrix& operator+=(const Matrix& other) {
    assert(rows_ == other.rows_);
    assert(cols_ == other.cols_);
    for (size_t row = 0; row < rows_; ++row) {
      for (size_t col = 0; col < cols_; ++col) {
        data_[row][col] += other(row, col);
      }
    }
    return (*this);
  }

  inline Matrix& operator-=(const Matrix& other) {
    assert(rows_ == other.rows_);
    assert(cols_ == other.cols_);
    for (size_t row = 0; row < rows_; ++row) {
      for (size_t col = 0; col < cols_; ++col) {
        data_[row][col] -= other(row, col);
      }
    }
    return (*this);
  }

  inline Matrix& operator*=(const Scalar& s) {
    for (size_t row = 0; row < rows_; ++row) {
      for (size_t col = 0; col < cols_; ++col) {
        data_[row][col] *= s;
      }
    }
    return (*this);
  }

  inline Matrix& operator/=(const Scalar& s) {
    Matrix res;
    for (size_t row = 0; row < rows_; ++row) {
      for (size_t col = 0; col < cols_; ++col) {
        data_[row][col] /= s;
      }
    }
    return (*this);
  }

  inline Scalar& operator()(size_t row, size_t col) {
    return data_[row][col];
  }

  inline Scalar operator()(size_t row, size_t col) const {
    return data_[row][col];
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t row = 0; row < matrix.RowSize(); ++row) {
      for (size_t col = 0; col < matrix.ColSize(); ++col) {
        os << std::left << std::setw(10) << matrix(row, col) << "\t";
      }
      os << std::endl;
    }
    return os;
  }

 private:
  size_t rows_;
  size_t cols_;
  Scalar data_[Rows][Cols];
};

}  // namespace math

#endif  // MATRIX_H_
