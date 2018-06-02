#ifndef WDGK_TRIANGLE_HEADER
#define WDGK_TRIANGLE_HEADER

#include "Shape.h"

class Triangle : public Shape {
public:
  int x1, y1, x2, y2, x3, y3;
  Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {
  }
  void draw(Image* img, Pen* pen) override;
  Shape* transform(Matrix* M) override;
};

#endif
