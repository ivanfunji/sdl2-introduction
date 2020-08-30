#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Window {
	public:
		SDL_Renderer *renderer;

	public:
		Window(const std::string title, int width, int height);
		~Window();
		bool init();
		void clear();
		inline bool isClosed() { return closed;};
		void pollEvents(SDL_Event &event);

	private:
		std::string title;
		SDL_Window *window;
		int width, height;
		bool closed = false;
};

Window::Window(const std::string _title, int w, int h) :
	title(_title), width(w), height(h)
{
	closed = !init();
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to load SDL2" << std::endl;
		return false;
	}

	window = SDL_CreateWindow("the window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Failed to create the window" << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Failed to create the renderer" << std::endl;
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		std::cerr << "Failed to load SDL_image" << std::endl;
		return false;
	}
	return true;
}

void Window::clear() {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 100, 1, 1, 255);
	SDL_RenderClear(renderer);
}

void Window::pollEvents(SDL_Event &event) {
	if (event.type == SDL_QUIT) {
		closed = true;
	}
}