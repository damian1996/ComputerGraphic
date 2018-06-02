#ifndef WDGK_BRESENHAM_HEADER
#define WDGK_BRESENHAM_HEADER

#include <iostream>

#include "image.h"
#include "pen.h"

class Line {
public:
    template<int tanx, int lr, int ud>
    static void drawLine(Image* temp, int* wsp, Pen* pen);
    static void line(Image* img, int x0, int y0, int x1, int y1, Pen* pen);
private:
    Line() {}
};

#endif
