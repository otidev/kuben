#ifndef DISK_H
#define DISK_H

#include "Include.h"
#include "Text.h"
#include "UI.h"

// Saves data to a specific file.
void SaveData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename);

// Loads data from a specific file.
void LoadData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename);

// Changes the filename the user saves to.
void ChangeSaveFilename(Text* infoText, char* saveFilename);

// Saves data to a specific file, with another filename.
// NOTE - This new filename becomes the primary filename after the program is run.
void SaveDataAs(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename);

#endif
