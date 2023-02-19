#include "Sprite.h"

void LoadSprite(Sprite* sprite, char* filename) {
	SDL_Surface* surf = IMG_Load(filename);
	if (surf == NULL) {
		fprintf(stderr, "Error: Couldn't load sprite image: %s", SDL_GetError());
	}

	sprite->width = sprite->rect.w = surf->w;
	sprite->height = sprite->rect.h = surf->h;
	sprite->rect.y = sprite->rect.x = 0;
	sprite->bitmap = SDL_CreateTextureFromSurface(globalWindow->renderer, surf);

	SDL_FreeSurface(surf);
}

void ChangeFrame(Sprite* sprite, int widthOfFrame, int heightOfFrame, int framesToMove) {
	sprite->rect.w = widthOfFrame;
	sprite->rect.h = heightOfFrame;

	sprite->rect.x += (widthOfFrame * framesToMove);
	if (sprite->rect.x >= sprite->width) {
		sprite->rect.x = 0;
		sprite->rect.y += heightOfFrame;
	} if (sprite->rect.x + sprite->rect.w <= 0) {
		sprite->rect.x = sprite->width - sprite->rect.w;
		sprite->rect.y -= heightOfFrame;
	} if (sprite->rect.y >= sprite->height) {
		sprite->rect.y = 0;
		sprite->rect.x = 0;
	} if (sprite->rect.y + sprite->rect.h <= 0) {
		sprite->rect.y = sprite->height - sprite->rect.h;
		sprite->rect.x = sprite->width - sprite->rect.w;
	}
}

uint32_t GetFrame(Sprite* sprite) {
	if (sprite->rect.x != 0 && (sprite->width % sprite->rect.x != 0) && (sprite->width % sprite->rect.x != sprite->rect.w)) {
		fprintf(stderr, "Error: X position (%d) of sprite does not align with its width (%d)!", sprite->rect.x, sprite->width);
		return -1;
	}

	if (sprite->rect.y != 0 && (sprite->height % sprite->rect.y != 0) && (sprite->height % sprite->rect.y != sprite->rect.h)) {
		fprintf(stderr, "Error: Y position (%d) of sprite does not align with its height (%d)!", sprite->rect.y, sprite->height);
		return -1;
	}

	// A little spaghetti code here. Sorry. (jk deal with it)
	return ((sprite->rect.x) ? (sprite->rect.x / sprite->rect.w) : 0) + ((sprite->rect.y) ? (sprite->rect.y / sprite->rect.h) : 0) * (sprite->width / sprite->rect.w);
}
