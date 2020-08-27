#include <stdio.h>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {

	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	//To use the SDL methods we need to initialize SDL
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf("Could not initialize SDL SDL_Error: %s\n", SDL_GetError());
	} else {
		//Create the window we'll be using
		window = SDL_CreateWindow("my second sdl window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if ( window == NULL) {
			printf("SDL Could not create the window SDL_Error: %s\n", SDL_GetError());
		} else {

			//Create a surface to put it on the window
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface with a color
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF));

			//Everytime a attribute of surface or window is changed it must be updated with  the function
			SDL_UpdateWindowSurface(window);

			SDL_Delay(5000);

			//Deallocate memory
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

	}

	return 0;
}
