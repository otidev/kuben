#include "Resources.h"

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
