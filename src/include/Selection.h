#ifndef SELECTION_H
#define SELECTION_H

#include "Include.h"
#include "UI.h"

extern bool redrawingRect;

bool PointRectColl(SDL_Rect* rect, Vec2* point);

bool PointRectCollF(SDL_FRect* rect, Vec2* point);

void HighlightRect(Box* rects[256], Box** paintedRect, int zoomFactor);

#endif