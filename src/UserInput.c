#include "UserInput.h"

void HandleZooming(Sprite* sprite, Box* rects[256]) {
	if (zoomFactor != 20 && globalWindow->mouseScroll.y > 0) {
		(zoomFactor)++;

		imageDestRect.x = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, (float)zoomFactor * sprite->width / frameWidth, (float)zoomFactor * sprite->width / frameWidth).x;
		imageDestRect.y = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, (float)zoomFactor * sprite->width / frameWidth, (float)zoomFactor * sprite->height / frameHeight).y;
	
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {

				rects[i]->rect.x /= ((float)zoomFactor - 1) * sprite->width / frameWidth;
				rects[i]->rect.y /= ((float)zoomFactor - 1) * sprite->height / frameHeight;
				rects[i]->rect.w /= ((float)zoomFactor - 1) * sprite->width / frameWidth;
				rects[i]->rect.h /= ((float)zoomFactor - 1) * sprite->height / frameHeight;

				rects[i]->rect.x *= (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.y *= (float)zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.w *= (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.h *= (float)zoomFactor * sprite->height / frameHeight;
			}
		}
	}
	
	if ((float)zoomFactor != 1 && globalWindow->mouseScroll.y < 0) {
		(zoomFactor)--;

		imageDestRect.x = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, (float)zoomFactor * sprite->width / frameWidth, (float)zoomFactor * sprite->width / frameWidth).x;
		imageDestRect.y = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, (float)zoomFactor * sprite->width / frameWidth, (float)zoomFactor * sprite->height / frameHeight).y;

		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x /= ((float)zoomFactor + 1) * sprite->width / frameWidth;
				rects[i]->rect.y /= ((float)zoomFactor + 1) * sprite->height / frameHeight;
				rects[i]->rect.w /= ((float)zoomFactor + 1) * sprite->width / frameWidth;
				rects[i]->rect.h /= ((float)zoomFactor + 1) * sprite->height / frameHeight;

				rects[i]->rect.x *= (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.y *= (float)zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.w *= (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.h *= (float)zoomFactor * sprite->height / frameHeight;
			}
		}
	}
}

void HandlePanning(Sprite* sprite, Box* rects[256]) {
	// Simple movement around the sprite
	if (globalWindow->keys[SDL_SCANCODE_W]) {
		imageDestRect.y += zoomFactor * sprite->height / frameHeight;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.y += (float)zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.h += (float)zoomFactor * sprite->height / frameHeight;
			}
		}
	}
	if (globalWindow->keys[SDL_SCANCODE_S]) {
		imageDestRect.y -= zoomFactor * sprite->height / frameHeight;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.y -= (float)zoomFactor * sprite->height / frameHeight;
				rects[i]->rect.h -= (float)zoomFactor * sprite->height / frameHeight;
			}
		}
	} if (globalWindow->keys[SDL_SCANCODE_A]) {
		imageDestRect.x += zoomFactor * sprite->width / frameWidth;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x += (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.w += (float)zoomFactor * sprite->width / frameWidth;
			}
		}
	} if (globalWindow->keys[SDL_SCANCODE_D]) {
		imageDestRect.x -= zoomFactor * sprite->width / frameWidth;
		for (int i = 0; i < 256; i++) {
			if (rects[i]) {
				rects[i]->rect.x -= (float)zoomFactor * sprite->width / frameWidth;
				rects[i]->rect.w -= (float)zoomFactor * sprite->width / frameWidth;
			}
		}
	}
}

void RecenterSprite(Sprite* sprite, Box* rects[256]) {
	Vec2 offset;
	offset.x = imageDestRect.x;
	offset.y = imageDestRect.y;

	CenterHoriz(&imageDestRect, &(SDL_Rect){0, 0, globalWindow->width, globalWindow->height});
	CenterVert(&imageDestRect, &(SDL_Rect){0, 0, globalWindow->width, globalWindow->height});
	imageDestRect.x = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameWidth / editSprite.rect.w).x;
	imageDestRect.y = TransposePixelGrid((Vec2){imageDestRect.x, imageDestRect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h).y;
	
	offset.x -= imageDestRect.x;
	offset.y -= imageDestRect.y;

	for (int i = 0; i < 256; i++) {
		if (rects[i]) {
			rects[i]->rect.x -= offset.x;
			rects[i]->rect.w -= offset.x;
			rects[i]->rect.y -= offset.y;
			rects[i]->rect.h -= offset.y;
			// rects[i]->rect.y += *zoomFactor * sprite->height / frameHeight;
			// rects[i]->rect.h += *zoomFactor * sprite->height / frameHeight;
		}
	}
}

void ChangeBoxColour(Box* box, WindowState state) {
	// Change colour info rect
	
	if (globalWindow->state != STATE_BOXCOLOUR_R && globalWindow->state != STATE_BOXCOLOUR_G && globalWindow->state != STATE_BOXCOLOUR_B && globalWindow->state != STATE_BOXCOLOUR_A) {
		memset(globalWindow->textInput, 0, sizeof(char) * 500);
		globalWindow->state = state;
	} else {
		if (globalWindow->keys[SDL_SCANCODE_BACKSPACE]) {
			for (int i = 0; i < 500; i++) {
				if (globalWindow->textInput[i] == 0) {
					globalWindow->textInput[i - 1] = 0;
					break;
				}
			}
		}


		int i;
		for (i = 0; i < 500; i++) {
			// If the char is not base-16, delete the char.
			if (globalWindow->textInput[i] == 0) {
				if (
					globalWindow->textInput[i - 1] != 'a'
					&& globalWindow->textInput[i - 1] != 'b'
					&& globalWindow->textInput[i - 1] != 'c'
					&& globalWindow->textInput[i - 1] != 'd'
					&& globalWindow->textInput[i - 1] != 'e'
					&& globalWindow->textInput[i - 1] != 'f'
					&& globalWindow->textInput[i - 1] != '1'
					&& globalWindow->textInput[i - 1] != '2'
					&& globalWindow->textInput[i - 1] != '3'
					&& globalWindow->textInput[i - 1] != '4'
					&& globalWindow->textInput[i - 1] != '5'
					&& globalWindow->textInput[i - 1] != '6'
					&& globalWindow->textInput[i - 1] != '7'
					&& globalWindow->textInput[i - 1] != '8'
					&& globalWindow->textInput[i - 1] != '9'
					&& globalWindow->textInput[i - 1] != '0'
				)
					globalWindow->textInput[i - 1] = 0;
					
				break;
			}
		}

		if (i == 3) {
			globalWindow->state = STATE_NORMAL;
			return;
		}

		if (i <= 2) {
			if (globalWindow->state == STATE_BOXCOLOUR_R)
				box->colour.r = (uint8_t)strtol(globalWindow->textInput, NULL, 16);
			if (globalWindow->state == STATE_BOXCOLOUR_G)
				box->colour.g = (uint8_t)strtol(globalWindow->textInput, NULL, 16);
			if (globalWindow->state == STATE_BOXCOLOUR_B)
				box->colour.b = (uint8_t)strtol(globalWindow->textInput, NULL, 16);
			if (globalWindow->state == STATE_BOXCOLOUR_A)
				box->colour.a = (uint8_t)strtol(globalWindow->textInput, NULL, 16);
		}

		
	}
}
