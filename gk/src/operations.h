#ifndef WDGK_OPERATIONS_HEADER
#define WDGK_OPERATIONS_HEADER

#include <iostream>
#include <string>
#include <map>
#include "image.h"
#include "clipwindow.h"

class Operations {
public:
  std::map<std::string, Image> images;
  std::map<std::string, ClippingWindow> windows;
	Operations();
  bool includePixel(const std::string& name, int x, int y);
  void load(const std::string& path, const std::string& name);
  void save(const std::string& path, const std::string& name);
  void create(const std::string& name, int wid, int hei);
  void put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b);
  void get(const std::string& name, int x, int y);
  void fill(const std::string& name, std::string& colorspace, float r, float g, float b);
  void clip(const std::string& name, int x1, int y1, int x2, int y2);
  void noclip(const std::string& name);
};

#endif
