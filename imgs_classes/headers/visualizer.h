#pragma once

#include <iostream>
#include <string>
#include "mloader.h"

class Visualizer {
	public:
		Visualizer(Window &_window, Media &_media);
		~Visualizer();
		void clear();
		void pollEvents(SDL_Event &event);

	private:
		Window window;
		Media media;
		SDL_Texture *texture;
		int index = 0;
};

Visualizer::Visualizer(Window &_window, Media &_media) :
	window(_window), media(_media)
{}

Visualizer::~Visualizer() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Visualizer::clear() {
	SDL_RenderClear(window.renderer);
	SDL_RenderCopy(window.renderer, texture, NULL, NULL);
}

void Visualizer::pollEvents(SDL_Event &event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_LEFT: 
				index--;
				texture = media.media[ abs(index % media.lenght) ];				
				break;


			case SDLK_RIGHT: 
				index++;
				texture = media.media[ abs(index % media.lenght) ];
				break;

			default:
				break;
		}
	}
}