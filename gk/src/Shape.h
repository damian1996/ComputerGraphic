#ifndef WDGK_SHAPE_HEADER
#define WDGK_SHAPE_HEADER

#include "Matrix.h"
#include "pen.h"
#include <string>
#include "image.h"

class Shape {
public:
  virtual void draw(Image* img, Pen* pen) = 0;
  virtual Shape* transform(Matrix* M) = 0;
  virtual ~Shape() {

  }
};

#endif
