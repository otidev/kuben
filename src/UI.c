#include "UI.h"

Vec2 TransposePixelGrid(Vec2 pixel, float gridSizeW, float gridSizeH) {
	Vec2 transposed = (Vec2){0};
	transposed.x = floor(pixel.x / gridSizeW) * gridSizeW;
	transposed.y = floor(pixel.y / gridSizeH) * gridSizeH;
	return transposed;
}

void DrawGrid(SDL_FRect rect, int widthPixel, int heightPixel) {
	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_BLEND);

	for (int i = widthPixel; i < rect.w; i += widthPixel) {
		SDL_SetRenderDrawColor(globalWindow->renderer, 128, 128, 128, 63);
		SDL_RenderDrawLineF(globalWindow->renderer, rect.x + i, rect.y, rect.x + i, rect.y + rect.h);
		SDL_SetRenderDrawColor(globalWindow->renderer, 255, 255, 255, 255);
	}

	for (int i = heightPixel; i < rect.h; i += heightPixel) {
		SDL_SetRenderDrawColor(globalWindow->renderer, 128, 128, 128, 128);
		SDL_RenderDrawLineF(globalWindow->renderer, rect.x, rect.y + i, rect.x + rect.w, rect.y + i);
		SDL_SetRenderDrawColor(globalWindow->renderer, 255, 255, 255, 255);
	}

	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_NONE);
}

void DrawPaintRect(Box* box, int zoomX, int zoomY) {
	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(globalWindow->renderer, box->colour.r, box->colour.b, box->colour.g, 127);

	SDL_RenderFillRect(globalWindow->renderer, &(SDL_Rect){
		TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).x,
		TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).y,
		TransposePixelGrid((Vec2){box->rect.w, box->rect.h}, zoomX, zoomY).x - TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).x,
		TransposePixelGrid((Vec2){box->rect.w, box->rect.h}, zoomX, zoomY).y - TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).y
	});


	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_NONE);


	SDL_SetRenderDrawColor(globalWindow->renderer, box->colour.r, box->colour.b, box->colour.g, 255);
	
	SDL_RenderDrawRect(globalWindow->renderer, &(SDL_Rect){
		TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).x,
		TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).y,
		TransposePixelGrid((Vec2){box->rect.w, box->rect.h}, zoomX, zoomY).x - TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).x,
		TransposePixelGrid((Vec2){box->rect.w, box->rect.h}, zoomX, zoomY).y - TransposePixelGrid((Vec2){box->rect.x, box->rect.y}, zoomX, zoomY).y
	});
	SDL_SetRenderDrawColor(globalWindow->renderer, 0x4c, 0x00, 0xb0, 255);
}

void DrawUIRects(int infoTextHeight) {
	UIBox topBarRect = (UIBox){(SDL_FRect){0, 0, 600, infoTextHeight + 3}, (SDL_Colour){0x5c, 0x00, 0xc0, 0x00}};
	UIBox bottomBarRect = (UIBox){(SDL_FRect){0, globalWindow->height - 75, 600, 75}, (SDL_Colour){0x5c, 0x00, 0xc0, 0x00}};

	SDL_SetRenderDrawColor(globalWindow->renderer, topBarRect.colour.r, topBarRect.colour.g, topBarRect.colour.b, 255);
	SDL_RenderFillRectF(globalWindow->renderer, &topBarRect.rect);
	SDL_RenderFillRectF(globalWindow->renderer, &bottomBarRect.rect);
	SDL_SetRenderDrawColor(globalWindow->renderer, 0x4c, 0x00, 0xb0, 255);
}