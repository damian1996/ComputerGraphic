#include "operations.h"

Operations::Operations() {
  
}

bool Operations::includePixel(const std::string& name, int x, int y) {
	if(!(x>=windows[name].x1 && x<windows[name].x2)) return false;
	if(!(y>=windows[name].y1 && y<windows[name].y2)) return false;
	return true;
}

void Operations::load(const std::string& path, const std::string& name) {
	images[name] = Image();
	images[name].readPNG(path);
	windows[name] = ClippingWindow(0, images[name].width(), 0, images[name].height(), &images[name]);
	//images.insert(std::pair<std::string, Image>(name, img));
}

void Operations::save(const std::string& path, const std::string& name) {
	images[name].writePNG(path);
}

void Operations::create(const std::string& name, int szer, int wys) {
	images[name] = Image(szer, wys);
	windows[name] = ClippingWindow(0, images[name].width(), 0, images[name].height(), &images[name]);
}

void Operations::put(const std::string& name, int x, int y, float r, float g, float b) {
	if(includePixel(name, x, y)) {
		RGBColor& tmp = images[name](x,y);
		tmp.r = r;
		tmp.g = g;
		tmp.b = b;
	}
}

void Operations::get(const std::string& name, int x, int y) {
	RGBColor tmp = images[name](x, y);
	std::cout << "R: <" << tmp.r << "> G: <" << tmp.g << "> B: <" << tmp.b << ">" << std::endl;
}

void Operations::fill(const std::string& name, float r, float g, float b) {
	for(int i=0; i<images[name].width(); i++) {
		for(int j=0; j<images[name].height(); j++) {
			put(name, i, j, r, g, b);
		}
	}
	//images[name].clear(RGBColor(r, g, b));
}

void Operations::clip(const std::string& name, int x1, int y1, int x2, int y2) {
	windows[name] = ClippingWindow(x1, x2, y1, y2, &images[name]);
}

void Operations::noclip(const std::string& name) {
	windows[name] = ClippingWindow(0, images[name].width(), 0, images[name].height(), &images[name]);
}
