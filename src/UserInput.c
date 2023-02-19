#include "UserInput.h"

void HandleZooming(int* zoomFactor, SDL_Rect* imageDestRect, Sprite* sprite, Box* rects[256]) {
	if (*zoomFactor != 20 && globalWindow->mouseScroll.y > 0) {
		(*zoomFactor)++;

		imageDestRect->x = TransposePixelGrid((Vec2){imageDestRect->x, imageDestRect->y}, (float)*zoomFactor * sprite->width / frameWidth, (float)*zoomFactor * sprite->width / frameWidth).x;
		imageDestRect->y = TransposePixelGrid((Vec2){imageDestRect->x, imageDestRect->y}, (float)*zoomFactor * sprite->width / frameWidth, (float)*zoomFactor * sprite->height / frameHeight).y;
	
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {

				rects[i]->rect.x /= ((float)*zoomFactor - 1) * sprite->width / frameWidth;
				rects[i]->rect.y /= ((float)*zoomFactor - 1) * sprite->height / frameHeight;
				rects[i]->rect.w /= ((float)*zoomFactor - 1) * sprite->width / frameWidth;
				rects[i]->rect.h /= ((float)*zoomFactor - 1) * sprite->height / frameHeight;

				rects[i]->rect.x *= (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.y *= (float)*zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.w *= (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.h *= (float)*zoomFactor * sprite->height / frameHeight;
			}
		}
	}
	
	if ((float)*zoomFactor != 1 && globalWindow->mouseScroll.y < 0) {
		(*zoomFactor)--;

		imageDestRect->x = TransposePixelGrid((Vec2){imageDestRect->x, imageDestRect->y}, (float)*zoomFactor * sprite->width / frameWidth, (float)*zoomFactor * sprite->width / frameWidth).x;
		imageDestRect->y = TransposePixelGrid((Vec2){imageDestRect->x, imageDestRect->y}, (float)*zoomFactor * sprite->width / frameWidth, (float)*zoomFactor * sprite->height / frameHeight).y;

		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x /= ((float)*zoomFactor + 1) * sprite->width / frameWidth;
				rects[i]->rect.y /= ((float)*zoomFactor + 1) * sprite->height / frameHeight;
				rects[i]->rect.w /= ((float)*zoomFactor + 1) * sprite->width / frameWidth;
				rects[i]->rect.h /= ((float)*zoomFactor + 1) * sprite->height / frameHeight;

				rects[i]->rect.x *= (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.y *= (float)*zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.w *= (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.h *= (float)*zoomFactor * sprite->height / frameHeight;
			}
		}
	}
}

void HandlePanning(int* zoomFactor, SDL_Rect* imageDestRect, Sprite* sprite, Box* rects[256]) {
	// Simple movement around the sprite
	if (globalWindow->keys[SDL_SCANCODE_W]) {
		imageDestRect->y += *zoomFactor * sprite->height / frameHeight;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.y += (float)*zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.h += (float)*zoomFactor * sprite->height / frameHeight;
			}
		}
	}
	if (globalWindow->keys[SDL_SCANCODE_S]) {
		imageDestRect->y -= *zoomFactor * sprite->height / frameHeight;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.y -= (float)*zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.h -= (float)*zoomFactor * sprite->height / frameHeight;
			}
		}
	} if (globalWindow->keys[SDL_SCANCODE_A]) {
		imageDestRect->x += *zoomFactor * sprite->width / frameWidth;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x += (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.w += (float)*zoomFactor * sprite->width / frameWidth;
			}
		}
	} if (globalWindow->keys[SDL_SCANCODE_D]) {
		imageDestRect->x -= *zoomFactor * sprite->width / frameWidth;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x -= (float)*zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.w -= (float)*zoomFactor * sprite->width / frameWidth;
			}
		}
	}
}
