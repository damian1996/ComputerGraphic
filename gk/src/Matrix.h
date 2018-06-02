#ifndef WDGK_MATRIX_HEADER
#define WDGK_MATRIX_HEADER

#include <vector>
#include <string>

class Matrix {
  std::string x;
  uint cols, rows;
  double *mat;
public:
  Matrix();
  Matrix(int cols, int rows, std::vector<double> values);
  ~Matrix();
  double get(uint i, uint j);
  void set(uint i, uint j, double val);
  void fill(std::vector<double> values);
  uint width();
  uint height();
};

#endif
