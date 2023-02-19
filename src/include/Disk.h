#ifndef DISK_H
#define DISK_H

#include "Include.h"
#include "Text.h"
#include "UI.h"

void SaveData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename);

void LoadData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename);
#endif
