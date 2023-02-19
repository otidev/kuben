#ifndef BITMAP_H
#define BITMAP_H

#include "Include.h"

void LoadSprite(Sprite* sprite, char* filename);

void ChangeFrame(Sprite* sprite, int widthOfFrame, int heightOfFrame, int framesToMove);

uint32_t GetFrame(Sprite* sprite);

#endif