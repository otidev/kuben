#ifndef WINDOW_H
#define WINDOW_H

#include "Include.h"

// Inits a window
int InitWindow(Window* window, int width, int height, char* name);

// Window event handling & alive checking
bool WindowIsOpen();

#endif
