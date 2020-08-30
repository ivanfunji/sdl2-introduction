#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

bool init();
bool loadMedia();
SDL_Texture* loadTexture(std::string path);

int main() {
	if (!init() & !loadMedia()) {
		return -1;
	}

	SDL_Event e;
	bool quit = false;

	while(!quit) {
		while(SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize");
		return false;
	}

	window = SDL_CreateWindow("my window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Error creating renderer");
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if ( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) ) {
		printf("sdl image could not start");
		return false;
	}

	return true;
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture *newTexture = NULL;

	SDL_Surface *newSurface = IMG_Load( path.c_str() );
	if (newSurface == NULL) {
		printf("Could not start surface image");
		return NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
	if (newTexture == NULL) {
		printf("Could not create texture");
		return NULL;
	}

	SDL_FreeSurface(newSurface);

	return newTexture;
}

bool loadMedia() {
	texture = loadTexture("files/download.bmp");
	if (texture == NULL) {
		printf("Could not load texture");
		return false;
	}
	return true;
}

void close() {
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	texture = NULL;
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

