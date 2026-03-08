#ifndef RGB_COLOR_H
#define RGB_COLOR_H

class RGBColor {
	public:
		float red;
		float green;
		float blue;

		RGBColor(float r, float g, float b);
		RGBColor();
		RGBColor operator+(const RGBColor &color) const;
};

#endif
