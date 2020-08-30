#include <string>
#include "headers/window.h"
#include "headers/rect.h"
#include <iostream>

void pollEvents(Window &window, Rect &rect) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		rect.pollEvents(event);
		window.pollEvents(event);
	}
}

int main(int argc, char **argv) {

	Window window("new sdl window", 640, 480);

	Color color(100, 0, 200, 255);
	Rect rect(window, 100, 100, 100, 100, color);

	while (!window.isClosed()) {
		pollEvents(window, rect);
		rect.draw();
		window.clear();
	}

	return 0;
}
