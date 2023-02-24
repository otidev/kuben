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

extern int frameWidth, frameHeight; // The width and height of one frame
extern int zoomFactor; // The zoom multiplier of the sprite
extern SDL_Rect imageDestRect; // Main sprite dstRect

// 2D Vector
typedef struct Vec2 {
	float x, y;
} Vec2;

// Different window states the window can be in
typedef enum WindowState {
	STATE_NORMAL = 0, // Normal drawing mode
	STATE_BOXCOLOUR_R, // Change box's red value
	STATE_BOXCOLOUR_G, // Change box's green value
	STATE_BOXCOLOUR_B, // Change box's blue value
	STATE_BOXCOLOUR_A, // Change box's alpha value
	STATE_SAVE_YN, // Save Y/N prompt
	STATE_SAVEAS, // Save as prompt
	STATE_CHANGESAVE, // Change save filename
} WindowState;

// Window struct
typedef struct Window {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	int width, height; // Width and height of window

	// Mouse things
	Vec2 mousePos; // Mouse position vector
	Vec2 mouseScroll; // Mapped according to SDL_MouseWheelEvent
	int mouseButtons[5]; // Mapped according to SDL_MouseButtonEvent

	// Keyboard things
	bool keys[512]; // Mapped according to SDL_Scancode
	char textInput[500]; // Gets *all* text typed (characters must be removed manually)

	bool fullscreen;
	bool running;

	WindowState state; // Window state
} Window;

extern Window* globalWindow; // The window pointer that everything can see/use

// Sprite struct
typedef struct Sprite {
	SDL_Texture* bitmap;
	SDL_Rect rect; // This can be dstRect or srcRect, context matters
	int width, height; // Width and height of sprite
} Sprite;

extern Sprite editSprite; // The sprite we use to edit

typedef struct Text {
	TTF_Font* font;
	Sprite sprite;
} Text;

// A rect used in UI
typedef struct UIBox {
	SDL_FRect rect;
	SDL_Colour colour;
} UIBox;

// For more detail about the following structs' members, check kuben/docs/FileFormat.md

// Box struct
typedef struct Box {
	uint8_t identifier;
	uint32_t framePos;
	SDL_FRect rect;
	SDL_Colour colour;
} Box;

// Datatypes found in the file

// The header the .kuben file
typedef struct KBN_Header {
	uint8_t magicNum[4];
	uint8_t numBoxes;
} __attribute__((packed)) KBN_Header;

// A box in the .kuben file
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
