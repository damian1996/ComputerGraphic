#ifndef WDGK_COLOR_HEADER
#define WDGK_COLOR_HEADER

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

#endif
