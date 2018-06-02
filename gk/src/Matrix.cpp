#include "Matrix.h"

Matrix::Matrix() : cols(0), rows(0) {
}
Matrix::Matrix(int cols, int rows, std::vector<double> values) : cols(cols), rows(rows) {
  mat = new double[rows*cols];
  fill(values);
}
Matrix::~Matrix() {
  delete [] mat;
}

double Matrix::get(uint i, uint j) {
  return mat[i*cols + j];
}
void Matrix::set(uint i, uint j, double val) {
  mat[i*cols + j] = val;
}
void Matrix::fill(std::vector<double> values) {
  for(int i=0; i<height(); i++) {
    for(int j=0; j<width(); j++) {
      mat[i*cols + j] = values[i*cols + j];
    }
  }
}
uint Matrix::width() {
  return cols;
}
uint Matrix::height() {
  return rows;
}
