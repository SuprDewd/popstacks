#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <algorithm>
#include "polynomial_rational.hpp"

polynomial_rational abs(polynomial_rational x) {
    return x < polynomial_rational::zero() ? -x : x;
}

bool eq(polynomial_rational a, polynomial_rational b) { return a == b; }
struct matrix {
  int rows, cols, cnt; std::vector<polynomial_rational> data;
  inline polynomial_rational& at(int i, int j) { return data[i * cols + j]; }
  matrix(int r, int c) : rows(r), cols(c), cnt(r * c) {
    data.assign(cnt, polynomial_rational::zero()); }
  matrix(const matrix& other) : rows(other.rows),
    cols(other.cols), cnt(other.cnt), data(other.data) { }
  ~matrix() {
  }
  matrix& operator=(const matrix &other) {
      rows = other.rows;
      cols = other.cols;
      cnt = other.cnt;
      data = other.data;
      return *this;
  }
  polynomial_rational& operator()(int i, int j) { return at(i, j); }
  matrix operator +(const matrix& other) {
    matrix res(*this);
    for (int i = 0; i < cnt; i++)
      res.data[i] = res.data[i] + other.data[i];
    return res; }
  matrix operator -(const matrix& other) {
    matrix res(*this);
    for (int i = 0; i < cnt; i++)
      res.data[i] = res.data[i] - other.data[i];
    return res; }
  matrix operator *(polynomial_rational other) {
    matrix res(*this);
    for (int i = 0; i < cnt; i++)
        res.data[i] = res.data[i] * other;
    return res; }
  matrix operator *(const matrix& other) {
    matrix res(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int k = 0; k < cols; k++)
            for (int j = 0; j < other.cols; j++)
                res(i, j) = res(i, j) + at(i, k) * other.data[k * other.cols + j];
    return res; }
  matrix pow(long long p) {
    matrix res(rows, cols), sq(*this);
    for (int i = 0; i < rows; i++) res(i, i) = polynomial_rational::one();
    while (p) {
      if (p & 1) res = res * sq;
      p >>= 1;
      if (p) sq = sq * sq;
    } return res; }
  matrix rref(polynomial_rational &det, int &rank) {
    matrix mat(*this); det = polynomial_rational::one(), rank = 0;
    for (int r = 0, c = 0; c < cols; c++) {
      int k = r;
      for (int i = k+1; i < rows; i++) if (abs(mat(k,c)) < abs(mat(i,c))) k = i;
      if (k >= rows || eq(mat(k, c), polynomial_rational::zero())) continue;
      if (k != r) {
        det = det * (-polynomial_rational::one());
        for (int i = 0; i < cols; i++) std::swap(mat.at(k, i), mat.at(r, i));
      } det = det * mat(r, r); rank++;
      polynomial_rational d = mat(r,c);
      for (int i = 0; i < cols; i++) mat(r, i) = mat(r, i) / d;
      for (int i = 0; i < rows; i++) {
        polynomial_rational m = mat(i, c);
        if (i != r && !eq(m, polynomial_rational::zero()))
          for (int j = 0; j < cols; j++) mat(i, j) = mat(i, j) - m * mat(r, j);
      } r++;

        // for (int i = 0; i < rows; i++) {
        //     for (int j = 0; j < cols; j++) {
        //         std::cout << mat.at(i,j) << "\t";
        //     }
        //     std::cout << std::endl;
        // }
        // std::cout << std::endl;

    } return mat; }
  matrix transpose() {
    matrix res(cols, rows);
    for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) res(j, i) = at(i, j);
    return res; }
  void swap_rows(int x, int y) {
      for (int i = 0; i < cols; i++) {
          // polynomial_rational tmp = at(x,i);
          // at(x,i) = at(y,i);
          // at(y,i) = tmp;
          std::swap(at(x,i), at(y,i));
      }
  }
  void add_row(int from, int to, polynomial_rational mul) {
      for (int i = 0; i < cols; i++) {
          at(to, i) = at(to, i) + mul * at(from, i);
      }
  }
  void mul_row(int r, polynomial_rational mul) {
      for (int i = 0; i < cols; i++) {
          at(r, i) = at(r, i) * mul;
      }
  }
};

#endif
