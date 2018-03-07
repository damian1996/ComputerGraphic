#include "operations.h"
#include <iostream>
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

void Operations::put(const std::string& name, int x, int y, std::string& colorspace, float r, float g, float b) {
	//std::cout << conv.r << std::endl;
	if(includePixel(name, x, y)) {
    RGBColor& tmp = images[name](x,y);
    RGBColor conv = RGBColor(r, g, b);
		if(colorspace=="lrgb") { // LRGBtoSRGB
			  conv = conv.gamma(1.0/2.2);
			  conv = conv.clamp();
		}
    else if(colorspace=="xyz") { // XYZtoSRGB
      float xyz[3] = {r, g, b};
      float lin[3] = {0, 0, 0};
      for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
          for(int k=0; k<1; k++) {
            lin[i] += (trR[i][j]*xyz[j]);
          }
        }
      }
			conv = RGBColor(lin[0], lin[1], lin[2]);
			conv = conv.clamp();
			conv = conv.gamma(1/2.2);
    }
		tmp.r = conv.r;
		tmp.g = conv.g;
		tmp.b = conv.b;
	}
}

void Operations::get(const std::string& name, int x, int y, const std::string& colorspace) {
	RGBColor tmp = images[name](x, y);
	if(colorspace=="lrgb") {
		tmp = tmp.gamma(2.2);
		tmp = tmp.clamp();
		//(srgb → lrgb, srgb → xyz)
	}
	else if(colorspace=="xyz") {
		tmp = tmp.gamma(2.2);
		tmp = tmp.clamp();
		float lin[3] = {tmp.r, tmp.g, tmp.b};
		float xyz[3] = {0, 0, 0};
		for(int i=0; i<3; i++) {
			for(int j=0; j<3; j++) {
				for(int k=0; k<1; k++) {
					xyz[i] += (tr[i][j]*lin[j]);
				}
			}
		}
		tmp = RGBColor(xyz[0], xyz[1], xyz[2]);
		tmp = tmp.clamp();
	}
	std::cout << colorspace << " " << tmp.r << " " << tmp.g << " " << tmp.b << std::endl;
}

void Operations::fill(const std::string& name, std::string& colorspace, float r, float g, float b) {
	for(int i=0; i<images[name].width(); i++) {
		for(int j=0; j<images[name].height(); j++) {
			put(name, i, j, colorspace, r, g, b);
		}
	}
}

void Operations::clip(const std::string& name, int x1, int y1, int x2, int y2) {
	windows[name] = ClippingWindow(x1, x2, y1, y2, &images[name]);
}

void Operations::noclip(const std::string& name) {
	windows[name] = ClippingWindow(0, images[name].width(), 0, images[name].height(), &images[name]);
}

void Operations::shrink(const std::string& name, int n) {
	int x = images[name].width()/n, y = images[name].height()/n;
  Image img = Image(x, y);
	//printf("%d %d\n", images[name].width()/n, images[name].height()/n);
	for(int i=0; i<img.width(); i++) {
			for(int j=0; j<img.height(); j++) {
					float tmpR=0, tmpG=0, tmpB=0;
					for(int k=i*n; k<(i+1)*n; k++) {
							for(int l=j*n; l<(j+1)*n; l++) {
									if(i==3 && j==6) {
									}
									RGBColor tmp = images[name](k, l);
									tmpR += tmp.r;
									tmpG += tmp.g;
									tmpB += tmp.b;
							}
					}
					RGBColor& shrinkImg = img(i, j);
					shrinkImg.r = tmpR/n*n;
					shrinkImg.g = tmpG/n*n;
					shrinkImg.b = tmpB/n*n;
			}
	}
  images[name] = img;
}

// że najpierw przeliczasz srgb → lrgb, liczysz średnią, a potem z powrotem

void Operations::merge(const std::string& name1, const std::string& name2, float weight) {

}
