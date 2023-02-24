// Resources.h: A couple of functions everything should use.

#ifndef RESOURCES_H
#define RESOURCES_H

#include "Include.h"

// Returns true if there is collision (overlapping) between a Vec2 and a SDL_Rect
bool PointRectColl(SDL_Rect* rect, Vec2* point);

// Returns true if there is collision (overlapping) between a Vec2 and a SDL_FRect
bool PointRectCollF(SDL_FRect* rect, Vec2* point);

// Centers an SDL_Rect horizontally
void CenterHoriz(SDL_Rect* a, SDL_Rect* b);

// Centers an SDL_Rect vertically
void CenterVert(SDL_Rect* a, SDL_Rect* b);

#endif
