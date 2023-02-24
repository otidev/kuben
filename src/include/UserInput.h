#ifndef USERINPUT_H
#define USERINPUT_H

#include "Include.h"
#include "UI.h"

// UNUSED (for now)
void HandleZooming(Sprite* sprite, Box* rects[256]);

// Handles panning around a sprite
void HandlePanning(Sprite* sprite, Box* rects[256]);

// Recenters a sprite and boxes to the middle of the screen
void RecenterSprite(Sprite* sprite, Box* rects[256]);

// Changes a box colour (state = STATE_BOXCOLOUR_*)
void ChangeBoxColour(Box* box, WindowState state);

#endif
