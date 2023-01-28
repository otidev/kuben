#ifndef UI_H
#define UI_H

#include "Include.h"

Vec2 TransposePixelGrid(Vec2 pixel, float gridSizeW, float gridSizeH);

void DrawGrid(SDL_FRect rect, int widthPixel, int heightPixel);

void DrawPaintRect(Box* box, int zoomX, int zoomY);

void DrawUIRects(int infoTextHeight);

#endif