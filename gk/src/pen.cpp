#include "pen.h"

Pen::Pen(float r, float g, float b) {
    col = new RGBColor(r, g, b);
}

Pen::~Pen() {
    delete col;
}