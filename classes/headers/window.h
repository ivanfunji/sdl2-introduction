#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Window {
	public:
		Window(const std::string &_title, int _width, int _height);
		~Window();
		void pollEvents(SDL_Event &event);
		void clear();
		inline bool isClosed() const { return closed; };
		SDL_Renderer *renderer = nullptr;
		bool closed = false;

	private:
		bool init();

	private:
		std::string title;
		int width;
		int height;

		SDL_Window *window = nullptr;
};

Window::Window(const std::string &_title, int _width, int _height) :
	title(_title), width(_width), height(_height)
{
	closed = !init();
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL" << std::endl;
		return false;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cerr << "Failed to create window" <<std:: endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		std::cerr << "Failed to create renderer" <<std:: endl;
		return false;
	}

	return true;
}

void Window::pollEvents(SDL_Event &event) {
	switch (event.type) {
		case SDL_QUIT:
			closed = true;
			break;

		default:
			break;
	}
}

void Window::clear() {
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 200, 100, 0, 255);
	SDL_RenderClear(renderer);
}
