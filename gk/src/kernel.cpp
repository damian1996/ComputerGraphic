#include "kernel.h"

// x ile kolumn
// y ile wierszy

Kernel::Kernel(uint cols, uint rows) : cols(cols), rows(rows){
  tab = new float*[rows];
  for(int i=0; i<rows; i++) {
    tab[i] = new float[rows];
  }
}

Kernel::~Kernel() {
  cols = rows = 0;
  for(int i=0; i<rows; i++)
      delete [] tab[i];
  delete [] tab;
}

void Kernel::fill(std::vector<float>& vec) {
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      tab[i][j] = vec[i*cols + j];
    }
  }
}

/*float& Kernel::operator()(uint k, uint l) {
  int i = (rows-1)/2, j=(cols-1)/2;
  return tab[k+j][l+i];
}

const float& Kernel::operator()(uint k, uint l) const {
  int i = (x-1)/2, j=(y-1)/2;
  return tab[k+j][l+i];
}*/

uint Kernel::width() {
  return cols;
}

uint Kernel::height() {
  return rows;
}
