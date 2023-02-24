#ifndef BITMAP_H
#define BITMAP_H

#include "Include.h"

// Loads a sprite
void LoadSprite(Sprite* sprite, char* filename);

// Changes the frame of a sprite
// If framesToMove is negative it will move back in frames, if not it will move forward
void ChangeFrame(Sprite* sprite, int widthOfFrame, int heightOfFrame, int framesToMove);

uint32_t GetFrame(Sprite* sprite);

#endif
