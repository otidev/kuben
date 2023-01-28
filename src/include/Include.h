#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define FPS 45

extern int frameWidth, frameHeight;

typedef struct Vec2 {
	float x, y;
} Vec2;

typedef struct Window {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	int width, height;

	// Mouse things
	Vec2 mousePos;
	Vec2 mouseScroll;
	int mouseButtons[5];

	// Keyboard things
	bool keys[512];

	bool fullscreen;
	bool running;
} Window;

extern Window* globalWindow;

typedef struct Sprite {
	SDL_Texture* bitmap;
	SDL_Rect rect;
	int width, height;
} Sprite;

typedef struct Box {
	int identifier; 
	SDL_FRect rect;
	SDL_Colour colour;
} Box;

typedef struct UIBox {
	SDL_FRect rect;
	SDL_Colour colour;
} UIBox;

typedef struct Text {
	TTF_Font* font;
	Sprite sprite;
} Text;

#endif