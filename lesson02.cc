//
// SDL2pp tutorial
//
// Written in 2015 by Dmitry Marakasiv <amdmi3@amdmi3.ru>
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with
// this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//

//
// Lesson 02:
//
// - Main loop
// - Event processing
//

#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int main() try {
	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprites image as a new texture
	Texture sprites(renderer, DATA_PATH "/M484SpaceSoldier.png");

	// Main loop
	while (1) {
		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				}
			}
		}

		int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center

		// Clear screen
		renderer.Clear();

		// Draw player sprite
		renderer.Copy(
				sprites,
				Rect(8, 11, 50, 50),
				Rect(0, vcenter - 50, 50, 50)
			);

		// Show rendered frame
		renderer.Present();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
	}

	// Here all resources are automatically released and library deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
