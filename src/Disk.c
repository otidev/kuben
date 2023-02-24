#include "Disk.h"

void SaveData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename) {
	if (access(saveFilename, F_OK) == 0 && (globalWindow->state != STATE_SAVEAS)) {
		char warningMessage[500];
		snprintf(warningMessage, 500, "Warning: The file \"%s\" exists, overwrite? (Y)es/(N)o", saveFilename);
		CreateText(infoText, warningMessage, 600, (SDL_Colour){255, 255, 255, 255});
	
		if (globalWindow->state == STATE_SAVE_YN) {
			if (globalWindow->keys[SDL_SCANCODE_Y]) {
				globalWindow->state = STATE_NORMAL;
			} else if (globalWindow->keys[SDL_SCANCODE_N]) {
				globalWindow->state = STATE_NORMAL;
				CreateText(infoText, origInfoString, 600, (SDL_Colour){255, 255, 255, 255});
				return;
			} else {
				return;
			}
		} else {
			globalWindow->state = STATE_SAVE_YN;
			return;
		}
	}

	FILE* file = fopen(saveFilename, "wb");
	
	uint8_t i;
	for (i = 0;; i++) {
		// If the next box is nulled, we have the last used box and break
		if (rects[i] == NULL)
			break;
	}

	int fileSize = sizeof(KBN_Header) + (sizeof(KBN_Box) * i);
	char fileBuf[fileSize];
	int locationInFile = 0;

	KBN_Header header = (KBN_Header){{'K', 'U', 0x17, 0x1}, i};
	memcpy(fileBuf + locationInFile, &header, sizeof(KBN_Header));
	locationInFile += sizeof(KBN_Header);

	KBN_Box boxes[i];
	for (int j = 0; j < i; j++) {
		// we don't need to check this, but we check this.
		if (rects[j]) {
			boxes[j] = (KBN_Box) {
				rects[j]->identifier,
				rects[j]->framePos,
				(int)TransposeGridPixel((Vec2){rects[j]->rect.x, rects[j]->rect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x,
				(int)TransposeGridPixel((Vec2){rects[j]->rect.x, rects[j]->rect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y,
				(int)(TransposeGridPixel((Vec2){rects[j]->rect.w, rects[j]->rect.h}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x - TransposeGridPixel((Vec2){rects[j]->rect.x, rects[j]->rect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x),
				(int)(TransposeGridPixel((Vec2){rects[j]->rect.w, rects[j]->rect.h}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y - TransposeGridPixel((Vec2){rects[j]->rect.x, rects[j]->rect.y}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y),
				rects[j]->colour.r,
				rects[j]->colour.g,
				rects[j]->colour.b,
				rects[j]->colour.a,
			};
			memcpy(fileBuf + locationInFile, &boxes[j], sizeof(KBN_Box));
			locationInFile += sizeof(KBN_Box);
		}
	}

	char savedSMessage[500];
	snprintf(savedSMessage, 500, "Saved data to -> %s", saveFilename);
	CreateText(infoText, savedSMessage, 600, (SDL_Colour){255, 255, 255, 255});

	fwrite(fileBuf, fileSize, 1, file);
	fclose(file);
}

void LoadData(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename) {
	FILE* file = fopen(saveFilename, "rb");

	// Thanks, moonengine
	fseek(file, 0l, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0l, SEEK_SET);
	
	char fileBuf[fileSize];
	int locationInFile = 0;
	fread(fileBuf, sizeof(char), fileSize, file);

	if (fileSize <= 0) {
		char errorMessage[500];
		snprintf(errorMessage, 500, "Error: The file \"%s\" doesn't exist", saveFilename);
		CreateText(infoText, errorMessage, 600, (SDL_Colour){255, 255, 255, 255});
		return;
	}

	KBN_Header header;
	memcpy(&header, fileBuf + locationInFile, sizeof(KBN_Header));
	locationInFile += sizeof(KBN_Header);

	if (
		!(header.magicNum[0] == 'K' 
		&& header.magicNum[1] == 'U'
		&& header.magicNum[2] == 0x17
		&& header.magicNum[3] == 0x1)
	) {
		char errorMessage[500];
		snprintf(errorMessage, 500, "Error: The file %s is not a .kuben file", saveFilename);
		CreateText(infoText, errorMessage, 600, (SDL_Colour){255, 255, 255, 255});
		return;
	}
	
	
	for (int j = 0; j < header.numBoxes; j++) {
		KBN_Box box;
		SDL_zero(box); // Could've used memset but who cares
		memcpy(&box, fileBuf + locationInFile, sizeof(KBN_Box));

		rects[j] = malloc(sizeof(Box));
		Box* tempBox = &(Box) {
			box.indentifier,
			box.framePos,
			(SDL_FRect) {
				(box.x * zoomFactor * ((float)frameWidth / editSprite.rect.w)) + imageDestRect.x,
				(box.y * zoomFactor * ((float)frameHeight / editSprite.rect.h)) + imageDestRect.y,
				(box.w * zoomFactor * ((float)frameWidth / editSprite.rect.w)) + ((box.x * zoomFactor * ((float)frameWidth / editSprite.rect.w)) + imageDestRect.x),
				(box.h * zoomFactor * ((float)frameHeight / editSprite.rect.h)) + ((box.y * zoomFactor * ((float)frameHeight / editSprite.rect.h)) + imageDestRect.y)
			},
			(SDL_Colour){box.r, box.g, box.b, box.a}
		};

		memcpy(rects[j], tempBox, sizeof(Box));
		
		locationInFile += sizeof(KBN_Box);
	}

	char loadedSMessage[500];
	snprintf(loadedSMessage, 500, "Loaded data from -> %s", saveFilename);
	CreateText(infoText, loadedSMessage, 600, (SDL_Colour){255, 255, 255, 255});
}

void ChangeSaveFilename(Text* infoText, char* saveFilename) {
	if (globalWindow->state != STATE_CHANGESAVE && globalWindow->state != STATE_SAVEAS) {
		memset(globalWindow->textInput, 0, sizeof(char) * 500);
		globalWindow->state = STATE_CHANGESAVE;
	}

	char changeFilenameMessage[500];
	char changeFilenameTmp[400];
	memset(changeFilenameTmp, 0, sizeof(char) * 400);

	if (globalWindow->keys[SDL_SCANCODE_BACKSPACE]) {
		for (int i = 0; i < 500; i++) {
			if (globalWindow->textInput[i] == 0) {
				globalWindow->textInput[i - 1] = 0;
				break;
			}
		}
	}

	memcpy(changeFilenameTmp, globalWindow->textInput, sizeof(char) * 400);

	snprintf(changeFilenameMessage, 500, "Change saving filename to -> %s", (changeFilenameTmp[0]) ? (changeFilenameTmp) : (" "));
	CreateText(infoText, changeFilenameMessage, 600, (SDL_Colour){255, 255, 255, 255});

	if (globalWindow->keys[SDL_SCANCODE_RETURN]) {
		memcpy(saveFilename, changeFilenameTmp, sizeof(char) * 400);
		globalWindow->state = STATE_NORMAL;
		
		snprintf(changeFilenameMessage, 500, "Changed filename to -> %s", changeFilenameTmp);
		CreateText(infoText, changeFilenameMessage, 600, (SDL_Colour){255, 255, 255, 255});
	}
}

void SaveDataAs(Box* rects[256], Text* infoText, char* origInfoString, char* saveFilename) {
	if (globalWindow->state != STATE_SAVEAS) {
		memset(globalWindow->textInput, 0, sizeof(char) * 500);
		globalWindow->state = STATE_SAVEAS;
	}
	
	ChangeSaveFilename(infoText, saveFilename);

	if (globalWindow->state == STATE_SAVEAS)
		return;

	SaveData(rects, infoText, origInfoString, saveFilename);
}
