#ifndef UI_H
#define UI_H

#include "Resources.h"
#include "Sprite.h"
#include "Include.h"
#include "Text.h"

Vec2 TransposePixelGrid(Vec2 pixel, float gridSizeW, float gridSizeH);

Vec2 TransposeGridPixel(Vec2 pixel, float gridSizeW, float gridSizeH, float offsetX, float offsetY);

void DrawGrid(SDL_FRect rect, int widthPixel, int heightPixel);

void DrawPaintRect(Box* box, Sprite* editSprite, int zoomX, int zoomY);

void DrawUIRects(int infoTextHeight, Text* boxInfo, bool boxInfoEmpty);

#endif