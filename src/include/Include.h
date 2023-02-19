#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define FPS 25

extern int frameWidth, frameHeight;
extern int zoomFactor;
extern SDL_Rect imageDestRect;

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
extern bool YNchoice, typing;


typedef struct Sprite {
	SDL_Texture* bitmap;
	SDL_Rect rect;
	int width, height;
} Sprite;

extern Sprite editSprite;

typedef struct Box {
	uint8_t identifier; 
	uint32_t framePos;
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

// Datatypes found in the file
typedef struct KBN_Header {
	uint8_t magicNum[4];
	uint8_t numBoxes;
} __attribute__((packed)) KBN_Header;

typedef struct KBN_Box {
	uint8_t indentifier;
	uint32_t framePos;
	
	// Box dimensions
	int x;
	int y;
	int w;
	int h;
	
	// Box colours
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} __attribute__((packed)) KBN_Box;

#endif