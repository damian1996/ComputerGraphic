#include "kernel.h"

Kernel::Kernel(uint x, uint y) : x(x), y(y){
  tab = new float*[x];
  for(int i=0; i<x; i++) {
    tab[i] = new float[y];
  }
}
Kernel::~Kernel() {
  x = y = 0;
  for(int i=0; i<x; i++)
      delete [] tab[i];
  delete [] tab;
}
void Kernel::fill(std::vector<float>& vec) {
  for(int i=0; i<x; i++) {
    for(int j=0; j<y; j++) {
      tab[i][j] = vec[i*y + j];
    }
  }
}
float& Kernel::operator()(uint k, uint l) {
  int i = (x-1)/2, j=(y-1)/2;
  return tab[k+i][l+j];
}
const float& Kernel::operator()(uint k, uint l) const {
  int i = (x-1)/2, j=(y-1)/2;
  return tab[k+i][l+j];
}

uint Kernel::width() {
  return x;
}

uint Kernel::height() {
  return y;
}
