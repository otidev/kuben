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

void CenterHoriz(SDL_Rect* a, SDL_Rect* b) {
	a->x = b->x;
	a->x += (b->w - a->w) / 2;
}

void CenterVert(SDL_Rect* a, SDL_Rect* b) {
	a->y = b->y;
	a->y += (b->h - a->h) / 2;
}
