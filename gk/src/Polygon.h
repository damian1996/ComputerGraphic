#ifndef WDGK_POLYGON_HEADER
#define WDGK_POLYGON_HEADER

#include <vector>

#include "Bresenham.h"
#include "color.h"
#include "Shape.h"

class Polygon : public Shape {
public:
    int n;
    std::vector<std::pair<double, double>> vert;
    Polygon(int n);
    Polygon(int n, const std::vector<std::pair<double, double>>& vert);
    ~Polygon();
    void draw(Image* img, Pen* pen) override;
    Polygon* transform(Matrix* M) override;
};


#endif
