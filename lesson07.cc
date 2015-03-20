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
// Lesson 07:
//
// - Text rendering
//

#include <iostream>
#include <exception>
#include <algorithm>
#include <string>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

int main() try {
	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Initialize SDL_ttf library
	SDLTTF ttf;

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprites image as a new texture; since there's no alpha channel
	// but we need transparency, use helper surface for which set color key
	// to color index 0 -> black background on image will be transparent on our
	// texture
	Texture sprites(renderer, Surface(DATA_PATH "/M484SpaceSoldier.png")
			.SetColorKey(true, 0));

	// Enable alpha blending for the sprites
	sprites.SetBlendMode(SDL_BLENDMODE_BLEND);

	// Gradient texture to be generated
	Texture gradient(renderer, SDL_PIXELFORMAT_BGR888, SDL_TEXTUREACCESS_STATIC, 1, 256);
	{
		// Array holding RGB values for 256 pixels
		unsigned char grad[256 * 3];
		int n = 0; // counter

		// Fill array with fading gray values from white to black; its contents will be
		// 255,255,255, 254,254,254, 253,253,253 ... 1,1,1, 0,0,0
		std::generate(grad, grad + sizeof(grad), [&](){ return 255 - n++ / 3; });

		// Update texture with our raw color data, enable blending and set color
		// and alpha modulation, so when rendered our texture will be dark cyan
		gradient.Update(NullOpt, grad, 3)
			.SetBlendMode(SDL_BLENDMODE_BLEND)
			.SetColorMod(0, 255, 255)
			.SetAlphaMod(85);
	}

	// Load font, 12pt size
	Font font(DATA_PATH "/Vera.ttf", 12);

	// Game state
	bool is_running = false; // whether the character is currently running
	int run_phase = -1;      // run animation phase
	float position = 0.0;    // player position

	unsigned int prev_ticks = SDL_GetTicks();
	// Main loop
	while (1) {
		// Timing: calculate difference between this and previous frame
		// in milliseconds
		unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;

		// Event processing:
		// - If window is closed, or Q or Escape buttons are pressed,
		//   quit the application
		// - If Right key is pressed, character would run
		// - If Right key is released, character would stop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				case SDLK_RIGHT: is_running = true; break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: is_running = false; break;
				}
			}
		}

		// Update game state for this frame:
		// if character is runnung, move it to the right
		if (is_running) {
			position += frame_delta * 0.2;
			run_phase = (frame_ticks / 100) % 8;
		} else {
			run_phase = 0;
		}

		// If player passes past the right side of the window, wrap him
		// to the left side
		if (position > renderer.GetOutputWidth())
			position = -50;

		int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center

		// Clear screen
		renderer.Clear();

		// Copy our gradient texture, stretching it to the whole window
		renderer.Copy(
				gradient,
				NullOpt,
				Rect(0, vcenter, renderer.GetOutputWidth(), renderer.GetOutputHeight() / 2)
			);

		// Pick sprite from sprite atlas based on whether
		// player is running and run animation phase
		int src_x = 8, src_y = 11; // by default, standing sprite
		if (is_running) {
			// one of 8 run animation sprites
			src_x = 8 + 51 * run_phase;
			src_y = 67;
		}

		// Draw player sprite
		sprites.SetAlphaMod(255); // sprite is fully opaque
		renderer.Copy(
				sprites,
				Rect(src_x, src_y, 50, 50),
				Rect((int)position, vcenter - 50, 50, 50)
			);

		// Draw the same sprite, below the first one, 50% transparent and
		// vertically flipped. It'll look like reflection in the mirror
		sprites.SetAlphaMod(127); // 50% transparent
		renderer.Copy(
				sprites,
				Rect(src_x, src_y, 50, 50),
				Rect((int)position, vcenter, 50, 50),
				0.0,              // don't rotate
				NullOpt,          // rotation center - not needed
				SDL_FLIP_VERTICAL // vertical flip
			);

		// Create text string to render
		std::string text =
			"Position: "
			+ std::to_string((int)position)
			+ ", running: "
			+ (is_running ? "true" : "false");

		// Render the text into new texture. Note that SDL_ttf render
		// text into Surface, which is converted into texture on the fly
		Texture text_sprite(
				renderer,
				font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255})
			);

		// Copy texture into top-left corner of the window
		renderer.Copy(text_sprite, NullOpt, Rect(0, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));

		// Show rendered frame
		renderer.Present();

		// Frame limiter: sleep for a little bit to not eat 100% of CPU
		SDL_Delay(1);
	}

	// Here all resources are automatically released and libraries deinitialized
	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
