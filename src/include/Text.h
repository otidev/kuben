#ifndef TEXT_H
#define TEXT_H

#include "Include.h"

// Loads a font
void LoadText(Text* text, int fontSize, char* srcFilename);

// Creates text from textLit
void CreateText(Text* text, char* textLit, int wrapWidth, SDL_Colour colour);

// Gets the *width* of a text
int GetTextSize(Text* text, char* textLit, int measureWidth);

#endif
