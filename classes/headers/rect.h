#pragma once

#include "window.h"
#include <iostream>

class Color {
	public:
		Color(int red, int green, int blue, int alpha);
		~Color();
		int r, g, b, a;
};

Color::Color(int red, int green, int blue, int alpha) :
	r(red), g(green), b(blue), a(alpha)
{}

Color::~Color() {
}

class Rect {
	public:
		Rect(Window &_window, int _w, int _h, int _x, int _y, Color &rgbColor);
		~Rect();
		void pollEvents(SDL_Event &event);
		void draw();

	private:
		int w, h;
		int x, y;
		Window window;
		Color color;
	    SDL_Rect rect;

};

Rect::Rect(Window &_window, int _w, int _h, int _x, int _y, Color &rgbColor) :
	window(_window), w(_w), h(_h), x(_x), y(_y), color(rgbColor)
{}

Rect::~Rect() {
}

void Rect::draw() {

    rect.w = w;
    rect.h = h;
    rect.x = x;
   	rect.y = y;

	SDL_SetRenderDrawColor(window.renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(window.renderer, &rect);
}

void Rect::pollEvents(SDL_Event &event) {
	if(event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				y+=10;
				break;

			case SDLK_UP:
				y-=10;
				break;

			case SDLK_LEFT:
				x-=10;
				break;

			case SDLK_RIGHT:
				x+=10;
				break;

			default: break;
		}
	}
}
