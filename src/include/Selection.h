#ifndef SELECTION_H
#define SELECTION_H

#include "Resources.h"
#include "Include.h"
#include "UI.h"

// If we are readjusting the size of a rectangle, this would be turned to true
extern bool redrawingRect;

// Redraws a rect
void RedrawRect(Box* rects[256], Box** paintedRect, int zoomFactor);

#endif
