#ifndef TEXT_H
#define TEXT_H

#include "Include.h"

void LoadText(Text* text, int fontSize, char* srcFilename);

void CreateText(Text* text, char* textLit, int wrapWidth, SDL_Colour colour);

#endif