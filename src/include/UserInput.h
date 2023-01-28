#ifndef USERINPUT_H
#define USERINPUT_H

#include "Include.h"
#include "UI.h"

void HandleZooming(int* zoomFactor, SDL_Rect* imageDestRect, Sprite* sprite, Box* rects[256]);

void HandlePanning(int* zoomFactor, SDL_Rect* imageDestRect, Sprite* sprite, Box* rects[256]);

#endif