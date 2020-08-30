#pragma once

#include <iostream>
#include <string>

class Media {
	public:
		Media(Window &_window);
		~Media();
		bool load();

	public:
		SDL_Texture *media[7];
		int lenght = sizeof(media) / sizeof(SDL_Texture*);

	private:
		Window window;
		SDL_Texture *loadTexture(const std::string path);

};

Media::Media(Window &_window) : 
	window(_window)
{}

Media::~Media() {}

bool Media::load() {

	media[0] = loadTexture("files/another.bmp");
	if (media[0] == nullptr) {
		return false;
	}

	media[1] = loadTexture("files/baboon.bmp");
	if (media[1] == nullptr) {
		return false;
	}

	media[2] = loadTexture("files/chevalier.bmp");
	if (media[2] == nullptr) {
		return false;
	}

	media[3] = loadTexture("files/download.bmp");
	if (media[3] == nullptr) {
		return false;
	}

	media[4] = loadTexture("files/nature.png");
	if (media[4] == nullptr) {
		return false;
	}

	media[5] = loadTexture("files/onemore.bmp");
	if (media[5] == nullptr) {
		return false;
	}

	media[6] = loadTexture("files/picture.jpeg");
	if (media[6] == nullptr) {
		return false;
	}

	return true;
}

SDL_Texture* Media::loadTexture (const std::string path) {
	SDL_Texture *loadedTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load( path.c_str() );

	if (loadedSurface == nullptr) {
		std::cerr << "Failed to load image surface" << std::endl;
	} else {
		loadedTexture = SDL_CreateTextureFromSurface(window.renderer, loadedSurface);
		if (loadedTexture == nullptr) {
			std::cerr << "Failed to create the texture" << std::endl;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return loadedTexture;
}