#pragma once

class Color {
	public:
		Color(int red, int green, int blue, int alpha);
		~Color();
		int r, g, b, a;
};

Color::Color(int red, int green, int blue, int alpha) :
	r(red), g(green), b(blue), a(aplha)
{}

Color::~Color(){}
