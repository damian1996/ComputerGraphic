#ifndef WDGK_CLIPPINGWINDOW_HEADER
#define WDGK_CLIPPINGWINDOW_HEADER

class ClippingWindow {
public:
	int x1, x2, y1, y2;
	Image* image;
	ClippingWindow();
	ClippingWindow(int x1, int x2, int y1, int y2, Image* image);
	ClippingWindow(const ClippingWindow& c);
	ClippingWindow& operator=(const ClippingWindow& c);
};

#endif
