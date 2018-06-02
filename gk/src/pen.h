#ifndef WDGK_PEN_HEADER
#define WDGK_PEN_HEADER

#include "color.h"

class Pen {
public:
    RGBColor* col;
    Pen(float r, float g, float b);
    ~Pen();
};


#endif
