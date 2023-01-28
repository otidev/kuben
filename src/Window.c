#include "Window.h"

Window* globalWindow;


int InitWindow(Window* window, int width, int height, char* name) {
	// Init things
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
		fprintf(stderr, "Error: Could not init SDL: %s", SDL_GetError());
		return 1;
	}

	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
		fprintf(stderr, "Error: Could not init SDL_image: %s", SDL_GetError());
		return 1;
	}
	
	if (TTF_Init() != 0) {
		fprintf(stderr, "Error: Could not init SDL_ttf: %s", SDL_GetError());
		return 1;
	}

	// Create window and renderer
	window->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (!window->window) {
		fprintf(stderr, "Error: Could not create an SDL Window: %s", SDL_GetError());
		return 1;
	}

	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!window->renderer) {
		fprintf(stderr, "Error: Could not create an SDL Renderer: %s", SDL_GetError());
		return 1;
	}

	// Window struct things
	window->mouseScroll.y = window->mouseScroll.x = 0;
	window->width = width;
	window->height = height;

	for (int i = 0; i < 5; i++)
		window->mouseButtons[i] = false;

	for (int i = 0; i < 512; i++) {
		window->keys[i] = false;
	}

	window->running = true;
	globalWindow = window;
	return 0;
}

static void HandleWindowEvents() {
	globalWindow->mouseScroll.y = globalWindow->mouseScroll.x = 0;
	while (SDL_PollEvent(&globalWindow->event)) {
		switch (globalWindow->event.type) {
			case SDL_QUIT:
				globalWindow->running = false;
				break;
			case SDL_MOUSEMOTION:
				globalWindow->mousePos.x = globalWindow->event.motion.x;
				globalWindow->mousePos.y = globalWindow->event.motion.y;
				break;
			case SDL_MOUSEWHEEL:
				globalWindow->mouseScroll.y = globalWindow->event.wheel.y;
				globalWindow->mouseScroll.x = globalWindow->event.wheel.x;
				break;
			case SDL_MOUSEBUTTONDOWN:
				globalWindow->mouseButtons[globalWindow->event.button.button - 1] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				globalWindow->mouseButtons[globalWindow->event.button.button - 1] = false;
				break;
			case SDL_KEYDOWN:
				globalWindow->keys[globalWindow->event.key.keysym.scancode] = true;
				break;
			case SDL_KEYUP:
				globalWindow->keys[globalWindow->event.key.keysym.scancode] = false;
				break;
		}
	}
}

bool WindowIsOpen() {
	HandleWindowEvents();

	return globalWindow->running;
}