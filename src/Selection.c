#include "Selection.h"

void RedrawRect(Box* rects[256], Box** paintedRect, int zoomFactor) {
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
			if (PointRectCollF(&calcRec, &globalWindow->mousePos) && !globalWindow->mouseButtons[0] && (GetFrame(&editSprite) == rects[i]->framePos)) {
				*paintedRect = rects[i];
				redrawingRect = true;
			}
		}
	}
}
