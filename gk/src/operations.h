#ifndef WDGK_OPERATIONS_HEADER
#define WDGK_OPERATIONS_HEADER

#include <iostream>
#include <string>
#include <map>
#include "image.h"
#include "clipwindow.h"

class Operations {
public:
  float trR[3][3] = {
    {3.2410, -1.5374, -0.4986},
    {-0.9692, 1.8760, 0.0416},
    {0.0556, -0.2040, 1.0570}
  };
  float tr[3][3] = {
    {0.4124, 0.3576, 0.1805},
    {0.2126, 0.7152, 0.0722},
    {0.0193, 0.1192, 0.9505}
  };
  std::map<std::string, Image> images;
  std::map<std::string, ClippingWindow> windows;
	Operations();
  bool includePixel(const std::string& name, int x, int y);
  void load(const std::string& path, const std::string& name);
  void save(const std::string& path, const std::string& name);
  void create(const std::string& name, int wid, int hei);
  void put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b);
  void get(const std::string& name, int x, int y, const std::string& colorspace);
  void fill(const std::string& name, std::string& colorspace, float r, float g, float b);
  void clip(const std::string& name, int x1, int y1, int x2, int y2);
  void noclip(const std::string& name);
  void shrink(const std::string& name, int n);
  void merge(const std::string& name1, const std::string& name2, float weight);
};

#endif
