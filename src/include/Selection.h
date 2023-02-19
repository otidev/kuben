#ifndef SELECTION_H
#define SELECTION_H

#include "Resources.h"
#include "Include.h"
#include "UI.h"

extern bool redrawingRect;

void HighlightRect(Box* rects[256], Box** paintedRect, int zoomFactor);

#endif