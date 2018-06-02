#ifndef WDGK_SECTION_HEADER
#define WDGK_SECTION_HEADER

#include "Shape.h"

class Section : public Shape {
public:
  int x1, y1, x2, y2;
  Section(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
  }
  void draw(Image* img, Pen* pen) override;
  Shape* transform(Matrix* M) override;
};

#endif
