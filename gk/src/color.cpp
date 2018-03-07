#include "assert.h"
#include "color.h"

RGBColor::RGBColor() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

RGBColor::RGBColor(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}


RGBColor RGBColor::clamp() const{
	RGBColor rgb(r, g, b);
	if(!(rgb.r>=0)) {
		rgb.r = 0;
	} else if(!(rgb.r<=1)) {
		rgb.r = 1;
	}
	if(!(rgb.g>=0)) {
		rgb.g = 0;
	} else if(!(rgb.g<=1)) {
		rgb.g = 1;
	}
	if(!(rgb.b>=0)) {
		rgb.b = 0;
	} else if(!(rgb.b<=1)) {
		rgb.b = 1;
	}
	return rgb;
}

RGBColor rep(float v) {
	RGBColor rgb;
	rgb.r = v;
	rgb.g = v;
	rgb.b = v;
	return rgb;
}

/*
class RGBColor {
  public:
    float r, g, b;

    RGBColor();
    RGBColor(float r, float g, float b);

    static RGBColor rep(float v);

    RGBColor operator+(const RGBColor& c) const;
    RGBColor operator-(const RGBColor& c) const;
    RGBColor operator*(const RGBColor& c) const;

    bool operator==(const RGBColor& b) const;
    bool operator!=(const RGBColor& b) const;

    RGBColor clamp() const;
    RGBColor gamma(float gam) const;
    float luminance() const;
};

RGBColor operator*(float scalar, const RGBColor& b);
RGBColor operator*(const RGBColor& a, float scalar);
RGBColor operator/(const RGBColor& a, float scalar);
*/
