#ifndef WDGK_KERNEL_HEADER
#define WDGK_KERNEL_HEADER

#include <iostream>
#include <vector>
#include <cmath>

class Kernel {
public:
  uint cols, rows;
  float **tab;
  Kernel(uint x, uint y);
  ~Kernel();
  void fill(std::vector<float> &);
  //float& operator()(uint x, uint y);
  //const float& operator()(uint x, uint y) const;
  uint width();
  uint height();
};

#endif
