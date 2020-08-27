#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

// Initialize SDL
bool init();

// Load the images
bool loadMedia();

// Free the images from memory
void close();

// Load one image and optimizes it
SDL_Surface* loadImageSurface(char *path);

enum SURFACES {
	SURFACE_0,
	SURFACE_1,
	SURFACE_2,
	SURFACE_3,
	SURFACE_4,
	SURFACE_TOTAL
};

SDL_Window *window;
SDL_Surface *screenSurface;
SDL_Surface *currentSurface;
SDL_Surface *keyPressSurfaces[SURFACE_TOTAL];

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int main() {

	if (!init()) {
		return -1;
	}
	loadMedia();

	SDL_Event e;
	bool quit = false;
	int indexSurface = 0;
	currentSurface = keyPressSurfaces[indexSurface];

	while (!quit) {

		// When a new event is created is detected by PoolEvent writing it on memory
		while(SDL_PollEvent(&e) != 0) {

			// The event is available
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_RIGHT:
					indexSurface++;
					currentSurface = keyPressSurfaces[abs(indexSurface % SURFACE_TOTAL)];
					printf("%d\n", abs(indexSurface % SURFACE_TOTAL));
					break;

					case SDLK_LEFT:
					indexSurface--;
					currentSurface = keyPressSurfaces[abs(indexSurface % SURFACE_TOTAL)];
					printf("%d\n", abs(indexSurface % SURFACE_TOTAL));
					break;

					default:
					break;
				}
			}
		}

		// Stretch image when is smaller than surface
		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(currentSurface, NULL, screenSurface, &stretchRect);

		// Show with orginal size
	//	SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}
	close();
	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL couldn't initialize SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("my new window",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Could not create the window SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	screenSurface = SDL_GetWindowSurface(window);
	return true;
}

bool loadMedia() {
	keyPressSurfaces[SURFACE_0] = loadImageSurface("file_images/another.bmp");
	keyPressSurfaces[SURFACE_1] = loadImageSurface("file_images/baboon.bmp");
	keyPressSurfaces[SURFACE_2] = loadImageSurface("file_images/chevalier.bmp");
	keyPressSurfaces[SURFACE_3] = loadImageSurface("file_images/download.bmp");
	keyPressSurfaces[SURFACE_4] = loadImageSurface("file_images/onemore.bmp");
	return true;
}

SDL_Surface* loadImageSurface(char *path) {
	SDL_Surface *imageSurface = SDL_LoadBMP( path );
	SDL_Surface *optimizedSurface = NULL;

	if (imageSurface == NULL) {
		printf("Couldn't load media SDL_Error: %s\n", SDL_GetError());
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface( imageSurface, screenSurface->format, 0);
	SDL_FreeSurface(imageSurface);

	if (optimizedSurface == NULL) {
		printf("Couldn't optimize image SDL_Error: %s\n", SDL_GetError());
	}

	return optimizedSurface;
}

void close() {
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_FreeSurface(screenSurface);
	screenSurface = NULL;
}
