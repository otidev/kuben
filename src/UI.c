#include "UI.h"

Vec2 TransposePixelGrid(Vec2 pixel, float gridSizeW, float gridSizeH) {
	Vec2 transposed = (Vec2){0};
	transposed.x = floor(pixel.x / gridSizeW) * gridSizeW;
	transposed.y = floor(pixel.y / gridSizeH) * gridSizeH;
	return transposed;
}

Vec2 TransposeGridPixel(Vec2 pixel, float gridSizeW, float gridSizeH, float offsetX, float offsetY) {
	Vec2 transposed = (Vec2){0};
	transposed.x = (TransposePixelGrid(pixel, gridSizeW, gridSizeH).x - offsetX) / gridSizeW;
	transposed.y = (TransposePixelGrid(pixel, gridSizeW, gridSizeH).y - offsetY) / gridSizeH;
	return transposed;
}

void DrawGrid(SDL_FRect rect, int widthPixel, int heightPixel) {
	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_BLEND);

	// Draw horizontal lines
	for (int i = widthPixel; i < rect.w; i += widthPixel) {
		SDL_SetRenderDrawColor(globalWindow->renderer, 128, 128, 128, 63);
		SDL_RenderDrawLineF(globalWindow->renderer, rect.x + i, rect.y, rect.x + i, rect.y + rect.h);
		SDL_SetRenderDrawColor(globalWindow->renderer, 255, 255, 255, 255);
	}

	// Draw vertical lines
	for (int i = heightPixel; i < rect.h; i += heightPixel) {
		SDL_SetRenderDrawColor(globalWindow->renderer, 128, 128, 128, 128);
		SDL_RenderDrawLineF(globalWindow->renderer, rect.x, rect.y + i, rect.x + rect.w, rect.y + i);
		SDL_SetRenderDrawColor(globalWindow->renderer, 255, 255, 255, 255);
	}

	SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_NONE);
}

void DrawPaintRect(Box* box, Sprite* editSprite, int zoomX, int zoomY) {

	// Don't draw rects if it doesn't belong to a frame
	if (GetFrame(editSprite) != box->framePos)
		return;

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

static void DrawUIBoxAndOutline(UIBox* UIBox, SDL_Colour* outlineColour) {
	SDL_SetRenderDrawColor(globalWindow->renderer, UIBox->colour.r, UIBox->colour.g, UIBox->colour.b, 255);
	SDL_RenderFillRectF(globalWindow->renderer, &UIBox->rect);
	if (PointRectCollF(&UIBox->rect, &globalWindow->mousePos)) {
		SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(globalWindow->renderer, outlineColour->r, outlineColour->g, outlineColour->b, 127);
		SDL_RenderFillRectF(globalWindow->renderer, &UIBox->rect);
		SDL_SetRenderDrawBlendMode(globalWindow->renderer, SDL_BLENDMODE_NONE);
	} else {
		SDL_SetRenderDrawColor(globalWindow->renderer, outlineColour->r, outlineColour->g, outlineColour->b, 255);
		SDL_RenderDrawRectF(globalWindow->renderer, &UIBox->rect);
	}
}

void DrawUIRects(int infoTextHeight, Text* boxInfo, bool boxInfoEmpty) {
	int lengthOfHex = GetTextSize(boxInfo, "00", 1000);
	UIBox topBarRect = (UIBox){(SDL_FRect){0, 0, 600, infoTextHeight + 3}, (SDL_Colour){0x5c, 0x00, 0xc0, 0x00}};
	UIBox bottomBarRect = (UIBox){(SDL_FRect){0, globalWindow->height - 75, 600, 75}, (SDL_Colour){0x5c, 0x00, 0xc0, 0x00}};
	UIBox colourInfoRectR = (UIBox){(SDL_FRect){GetTextSize(boxInfo, "Colours:  0", 10000), boxInfo->sprite.rect.y + (18 * 3 - 5), lengthOfHex, 18}, (SDL_Colour){0x47, 0x00, 0x95, 0x00}};
	UIBox colourInfoRectG = (UIBox){(SDL_FRect){GetTextSize(boxInfo, "Colours:  0x00 0x", 1000), boxInfo->sprite.rect.y + (18 * 3 - 5), lengthOfHex, 18}, (SDL_Colour){0x47, 0x00, 0x95, 0x00}};
	UIBox colourInfoRectB = (UIBox){(SDL_FRect){GetTextSize(boxInfo, "Colours:  0x00 0x00 0x ", 1000), boxInfo->sprite.rect.y + (18 * 3 - 5), lengthOfHex, 18}, (SDL_Colour){0x47, 0x00, 0x95, 0x00}};
	SDL_Colour infoRectOutline = (SDL_Colour){190, 169, 208, 0};

	SDL_SetRenderDrawColor(globalWindow->renderer, topBarRect.colour.r, topBarRect.colour.g, topBarRect.colour.b, 255);
	SDL_RenderFillRectF(globalWindow->renderer, &topBarRect.rect);
	SDL_SetRenderDrawColor(globalWindow->renderer, bottomBarRect.colour.r, bottomBarRect.colour.g, bottomBarRect.colour.b, 255);
	SDL_RenderFillRectF(globalWindow->renderer, &bottomBarRect.rect);

	if (!boxInfoEmpty) {
		DrawUIBoxAndOutline(&colourInfoRectR, &infoRectOutline);
		DrawUIBoxAndOutline(&colourInfoRectG, &infoRectOutline);
		DrawUIBoxAndOutline(&colourInfoRectB, &infoRectOutline);
	}

	SDL_SetRenderDrawColor(globalWindow->renderer, 0x4c, 0x00, 0xb0, 255);
}
