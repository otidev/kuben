#ifndef UI_H
#define UI_H

#include "Resources.h"
#include "Sprite.h"
#include "Include.h"
#include "Text.h"

extern UIBox topBarRect;
extern UIBox bottomBarRect;

// Transposes a pixel on the screen to a grid
Vec2 TransposePixelGrid(Vec2 pixel, float gridSizeW, float gridSizeH);

// Transposes a pixel on the grid to the screen
Vec2 TransposeGridPixel(Vec2 pixel, float gridSizeW, float gridSizeH, float offsetX, float offsetY);

// Draws a grid 
void DrawGrid(SDL_FRect rect, int widthOfPixel, int heightOfPixel);

// Draws a paint rect
void DrawPaintRect(Box* box, Sprite* editSprite, int zoomX, int zoomY);

// Draws rects in the UI
void DrawUIRects(int infoTextHeight, Text* boxInfo, bool boxInfoEmpty, Box* paintedRect);

#endif
