#ifndef WDGK_OPERATIONS_HEADER
#define WDGK_OPERATIONS_HEADER

#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include "image.h"
#include "kernel.h"
#include "clipwindow.h"

class Operations {
public:
  float x0 = 94.81;
  float y0 = 100.0;
  float z0 = 107.3;
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
  std::map<std::string, Kernel*> kernels;
	Operations();
  bool includePixel(const std::string& name, int x, int y);
  void load(const std::string& path, const std::string& name);
  void save(const std::string& name, const std::string& path);
  void create(const std::string& name, int wid, int hei);
  void put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b);
  void get(const std::string& name, int x, int y);
  //void get(const std::string& name, int x, int y, const std::string& colorspace);
  void fill(const std::string& name, std::string& colorspace, float r, float g, float b);
  void clip(const std::string& name, int x1, int y1, int x2, int y2);
  void noclip(const std::string& name);
  void shrink(const std::string& name, int n);
  void merge(const std::string& name1, const std::string& name2, float weight);
  void colorsplit(const std::string& name, const std::string& type);
  void compare(const std::string& name1, const std::string& name2);
  void kernel(const std::string& name, int x, int y, Kernel *k);
  void gamma(const std::string& out, const std::string& name, float val);
  void convolveimg(std::string& out, const std::string& in, const std::string& k);
  int clamp(int xp, int size);

};

#endif
