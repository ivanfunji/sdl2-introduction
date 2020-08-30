#include <string>
#include <iostream>
#include "headers/window.h"
#include "headers/visualizer.h"
#include "headers/mloader.h"

void pollEvents(Window &window, Visualizer &visualizer) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		visualizer.pollEvents(event);
		window.pollEvents(event);
	}
}

int main() {

	Window window("the window wdsd", 680, 420);
	Media media(window);

	if (!media.load()) {
		std::cerr << "Could not load the media files" << std::endl;
		return -1;
	} else {
		Visualizer visualizer(window, media);

		while(!window.isClosed()) {
			pollEvents(window, visualizer);
			visualizer.clear();
			window.clear();
		}
	}
	return 0;
}
