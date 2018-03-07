#include "image.h"
#include "clipwindow.h"

ClippingWindow::ClippingWindow() {
	  x1 = x2 = y1 = y2 = 0;
}

ClippingWindow::ClippingWindow(int x1, int x2, int y1, int y2, Image* image) {
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->image = image;
}

ClippingWindow::ClippingWindow(const ClippingWindow& c) : x1(c.x1), x2(c.x2), y1(c.y1), y2(c.y2) {
		image = c.image;
}
ClippingWindow& ClippingWindow::operator=(const ClippingWindow& c) {
		x1 = c.x1;
		x2 = c.x2;
		y1 = c.y1;
		y2 = c.y2;
		image = c.image;
}
