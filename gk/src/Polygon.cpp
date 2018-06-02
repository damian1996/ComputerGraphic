#include "Polygon.h"

Polygon::Polygon(int n) : n(n) {
  vert.resize(n);
}

Polygon::Polygon(int n, const std::vector<std::pair<double, double>>& vert) : n(n) {
  this->vert = std::move(vert);
}

Polygon::~Polygon() {
  this->vert.clear();
}

void Polygon::draw(Image* img, Pen* pen) {
  //#pragma omp parallel for
  for(int i=0; i<n-1; i++) {
    //std::cout << std::round(vert[i].first) << " " << std::round(vert[i].second) << " " << std::round(vert[i+1].first) << " " << std::endl;
    Line::line(img, std::round(vert[i].first), std::round(vert[i].second), std::round(vert[i+1].first), std::round(vert[i+1].second), pen);
  }
  Line::line(img, std::round(vert[n-1].first), std::round(vert[n-1].second), std::round(vert[0].first), std::round(vert[0].second), pen);
}

Polygon* Polygon::transform(Matrix* M) {
    /*
    std::cout << "Matrix" << std::endl;
    for(int i=0; i<3; i++) {
      for(int j=0; j<3; j++) {
        std::cout << M->get(i, j) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    */
    Polygon* p = new Polygon(n);
    for(int i=0; i<n; i++) {
        double point[3] = {vert[i].first, vert[i].second, 1};
        for(int j=0; j<3; j++) p->vert[i].first += (point[j]*M->get(0, j));
        for(int j=0; j<3; j++) p->vert[i].second += (point[j]*M->get(1, j));
    }
    return p;
}
