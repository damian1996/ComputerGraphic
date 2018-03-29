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
}

void Operations::save(const std::string& name, const std::string& path) {
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
		else if(colorspace=="lab") { // LABtoSRGB
			float x = x0*pow((r+16)/116 + g/500, 3);
			float y = y0*pow((r+16)/116, 3);
			float z = z0*pow((r+16)/116 - b/200, 3);
			RGBColor c = RGBColor(x, y, z);
			c.clamp();
			float xyz[3] = {c.r, c.g, c.b};
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

void Operations::get(const std::string& name, int x, int y) {
	RGBColor tmp = images[name](x, y);
	std::cout << "R: " << tmp.r << " G: " << tmp.g << " B: " << tmp.b << "" << std::endl;
}

/*
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
	else if(colorspace=="lab") {
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
		float L = 116*cbrt(tmp.r/y0) - 16;
		float a = 500*(cbrt(tmp.r/x0) - cbrt(tmp.g/y0));
		float b = 200*(cbrt(tmp.g/y0) - cbrt(tmp.b/z0));
		tmp = RGBColor(L, a, b);
		tmp = tmp.clamp();
	}
	std::cout << colorspace << " " << tmp.r << " " << tmp.g << " " << tmp.b << std::endl;
}
*/

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
									RGBColor tmp = images[name](k, l);
									tmp.gamma(1.0/2.2);
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
	for(int i=0; i<img.width(); i++) {
		for(int j=0; j<img.height(); i++) {
			//RGBColor& afterGamma = img(i, j);
			//afterGamma.gamma(2.2);
		}
	}
  images[name] = img;
}

// że najpierw przeliczasz srgb → lrgb, liczysz średnią, a potem z powrotem

void Operations::merge(const std::string& name1, const std::string& name2, float w) {
	// czy mam to robic w clipping windows?
	RGBColor sec;
	int heightDraw2 = images[name2].height(), widthDraw2 = images[name2].width();
	for(int i=0; i<images[name1].width(); i++) {
		for(int j=0; j<images[name1].height(); j++) {
			RGBColor& first = images[name1](i, j);
			if(i<widthDraw2 && j<heightDraw2) {
				sec = images[name2](i, j);
			}
			first.r = w*first.r + (1-w)*sec.r;
			first.g = w*first.g + (1-w)*sec.g;
			first.b = w*first.b + (1-w)*sec.b;
			first.clamp();
		}
	}
}

void Operations::colorsplit(const std::string& name, const std::string& type) {
	int wid = images[name].width(), hei = images[name].height();
	for(int i=1; i<4; i++)
		create(name+std::to_string(i), wid, hei);

	for(int i=0; i<images[name].width(); i++) {
		for(int j=0; j<images[name].height(); j++) {
				RGBColor c = images[name](i,j);
				RGBColor& c1 = images[name+std::to_string(1)](i, j);
				c1.r = c1.g = c1.b = c.r;
				RGBColor& c2 = images[name+std::to_string(2)](i, j);
				c2.r = c2.g = c2.b = c.r;
				RGBColor& c3 = images[name+std::to_string(3)](i, j);
				c3.r = c3.g = c3.b = c.b;
		}
	}
}

void Operations::compare(const std::string& name1, const std::string& name2) {
		int n = images[name1].width(), k = images[name1].height();
		float sum = 0;
 		for(int i=0; i<n; i++) {
			for(int j=0; j<k; j++) {
				RGBColor img1 = images[name1](i, j);
				RGBColor img2 = images[name2](i, j);
				float val1 = pow(img1.r-img2.r, 2.0);
				float val2 = pow(img1.g-img2.g, 2.0);
				float val3 = pow(img1.b-img2.b, 2.0);
				sum += (val1+val2+val3);
			}
		}
		sum = sum/(3*n*k);
		printf("MSE %f\n", sum);
		float psnr = 10*log10(1.0/sum);
		printf("PSNR %f\n", psnr);
}

void Operations::kernel(const std::string& name, int x, int y, Kernel* k) {
	kernels[name] = k;
}

void Operations::gamma(const std::string& out, const std::string& name, float val) {
		int n = images[name].width(), k = images[name].height();
		for(int i=0; i<n; i++) {
				for(int j=0; j<k; j++) {
						images[out](i, j) = images[name](i, j).gamma(val);
				}
		}
}

void Operations::convolveimg(std::string& out, const std::string& in, const std::string& k) {
		int xX = images[in].width(), yY = images[in].height();
		create(out, xX, yY);
		for(int x = 0; x<xX; x++) {
				for(int y = 0; y<yY; y++) {
						RGBColor outImg;
	 					for(int p=0; p<kernels[k]->width(); p++) {
								for(int q=0; q<kernels[k]->height(); q++) {
										int xp=clamp(x-p, xX), yq=clamp(y-q, yY);
										RGBColor img = images[in](xp, yq);
										outImg.r += ((kernels[k]->tab[p][q])*img.r);
										outImg.g += ((kernels[k]->tab[p][q])*img.g);
										outImg.b += ((kernels[k]->tab[p][q])*img.b);
								}
						}
						images[out](x, y) = RGBColor(outImg.r, outImg.g, outImg.b);
				}
		}
}

int Operations::clamp(int xp, int size) {
	if(xp<0) return 0;
	else if(xp>=size) return size-1;
	else return xp;
}
