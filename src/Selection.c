#include "Selection.h"

bool PointRectColl(SDL_Rect* rect, Vec2* point) {
	if (
		point->x >= rect->x &&
		point->x <= rect->x + rect->w &&
		point->y >= rect->y &&
		point->y <= rect->y + rect->h
	)
		return true;
	else
		return false;
}

bool PointRectCollF(SDL_FRect* rect, Vec2* point) {
	if (
		point->x >= rect->x &&
		point->x <= rect->x + rect->w &&
		point->y >= rect->y &&
		point->y <= rect->y + rect->h
	)
		return true;
	else
		return false;
}

void HighlightRect(Box* rects[256], Box** paintedRect, int zoomFactor) {
	for (int i = 0; i < 256; i++) {
		if (!rects[i]) {
			break;
		}

		SDL_FRect calcRec = (SDL_FRect){
			TransposePixelGrid((Vec2){rects[i]->rect.x, rects[i]->rect.y}, zoomFactor, zoomFactor).x,
			TransposePixelGrid((Vec2){rects[i]->rect.x, rects[i]->rect.y}, zoomFactor, zoomFactor).y,
			TransposePixelGrid((Vec2){rects[i]->rect.w, rects[i]->rect.h}, zoomFactor, zoomFactor).x - TransposePixelGrid((Vec2){rects[i]->rect.x, rects[i]->rect.y}, zoomFactor, zoomFactor).x,
			TransposePixelGrid((Vec2){rects[i]->rect.w, rects[i]->rect.h}, zoomFactor, zoomFactor).y - TransposePixelGrid((Vec2){rects[i]->rect.x, rects[i]->rect.y}, zoomFactor, zoomFactor).y
		};

		// Redraw rect if not already in the process of (re)drawing
		if (!redrawingRect) {
			if (PointRectCollF(&calcRec, &globalWindow->mousePos) && !globalWindow->mouseButtons[0]) {
				*paintedRect = rects[i];
				redrawingRect = true;
			}
		}
	}
}