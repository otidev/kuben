#include "Include.h"
#include "Selection.h"
#include "UserInput.h"
#include "Disk.h"
#include "Window.h"
#include "Sprite.h"
#include "Text.h"
#include "UI.h"

Window window;
Sprite editSprite;
Text infoText;
Text boxInfoText;
bool boxInfoTextEmpty;
SDL_Rect imageDestRect;
int zoomFactor;
bool drawRect;
Box* rects[256];
Box* paintedRect;
char infoString[1000];
char rectInfoString[1000];
char* saveFilename;
bool redrawingRect = false;
SDL_Texture* editRenderTex;

int frameWidth, frameHeight;

int InitEverything(char* spriteName, int _frameWidth, int _frameHeight, char* _saveFilename) {
	if (InitWindow(&window, 1280, 720, "Kuben"))
		return 1;
	
	LoadSprite(&editSprite, spriteName);
	frameWidth = _frameWidth;
	frameHeight = _frameHeight;

	snprintf(infoString, 1000, "Frame width = %d    Frame height = %d\nFilename = %s", _frameWidth, _frameHeight, spriteName);

	LoadText(&infoText, 18, "assets/SourceCodePro-VariableFont_wght.ttf");
	LoadText(&boxInfoText, 18, "assets/SourceCodePro-VariableFont_wght.ttf");
	CreateText(&infoText, infoString, 600, (SDL_Colour){255, 255, 255, 255});

	ChangeFrame(&editSprite, frameWidth, frameHeight, 0);

	saveFilename = _saveFilename;

	SDL_StartTextInput();

	zoomFactor = 10;
	editRenderTex = SDL_CreateTexture(window.renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET, frameWidth * zoomFactor, frameHeight * zoomFactor);
	drawRect = true;

	for (int i = 0; i < 256; i++)
		rects[i] = NULL;

	return 0;
}

void DestroyEverything() {
	SDL_StopTextInput();
	SDL_DestroyRenderer(window.renderer);
	SDL_DestroyTexture(editSprite.bitmap);
	SDL_DestroyTexture(infoText.sprite.bitmap);
	SDL_DestroyTexture(boxInfoText.sprite.bitmap);
	SDL_DestroyTexture(editRenderTex);
	SDL_Quit();
}

// This is the actual painting of rects, not drawing them.
void PaintRectLit() {
	if (!(PointRectCollF(&topBarRect.rect, &globalWindow->mousePos) || PointRectCollF(&bottomBarRect.rect, &globalWindow->mousePos))) {
		if (window.mouseButtons[0]) {
			if (!drawRect) {
				drawRect = true;
				if (drawRect) {
					for (int i = 0; i < 256; i++) {
						if (rects[i] == NULL) {
							rects[i] = malloc(sizeof(Box));

							rects[i]->identifier = i;
							rects[i]->framePos = GetFrame(&editSprite);
							rects[i]->colour.r = rand() % 255;
							rects[i]->colour.g = rand() % 255;
							rects[i]->colour.b = rand() % 255;
							rects[i]->colour.a = 0;

							paintedRect = rects[i];
							break;
						}
					}
				}
				paintedRect->rect.x = window.mousePos.x;
				paintedRect->rect.y = window.mousePos.y;
			}

			paintedRect->rect.w = window.mousePos.x;
			paintedRect->rect.h = window.mousePos.y;

		} else if (window.mouseButtons[2] && paintedRect && (GetFrame(&editSprite) == paintedRect->framePos)) {
			paintedRect->rect.w = window.mousePos.x;
			paintedRect->rect.h = window.mousePos.y;
			redrawingRect = true;
		} else {
			redrawingRect = false;
			drawRect = false;
		}
	}
}

void Render() {
	SDL_SetRenderTarget(window.renderer, editRenderTex);

	SDL_SetRenderDrawColor(window.renderer, 0x4c, 0x00, 0xb0, 255);
	SDL_RenderClear(window.renderer);

	SDL_RenderCopy(window.renderer, editSprite.bitmap, &editSprite.rect, NULL);
	
	SDL_SetRenderTarget(window.renderer, NULL);

	SDL_RenderCopy(window.renderer, editRenderTex, NULL, &imageDestRect);

	DrawGrid((SDL_FRect){imageDestRect.x, imageDestRect.y, imageDestRect.w, imageDestRect.h}, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h);

	// Draw cursor
	SDL_SetRenderDrawColor(window.renderer, 255, 255, 255, 255);
	SDL_RenderFillRectF(window.renderer, &(SDL_FRect){
		TransposePixelGrid(window.mousePos, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h).x,
		TransposePixelGrid(window.mousePos, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h).y,
		zoomFactor * frameWidth / editSprite.rect.w,
		zoomFactor * frameHeight / editSprite.rect.h,
	});
	SDL_SetRenderDrawColor(window.renderer, 0x4c, 0x00, 0xb0, 255);

	for (int i = 0; i < 256; i++) {
		if (rects[i] != NULL) {
			DrawPaintRect(rects[i], &editSprite, zoomFactor * frameWidth / editSprite.rect.w, zoomFactor * frameHeight / editSprite.rect.h);
		}
	}

	DrawUIRects(infoText.sprite.height, &boxInfoText, boxInfoTextEmpty, paintedRect);
	SDL_RenderCopy(window.renderer, infoText.sprite.bitmap, NULL, &(SDL_Rect){0, 0, infoText.sprite.width, infoText.sprite.height});
	SDL_RenderCopy(window.renderer, boxInfoText.sprite.bitmap, NULL, &boxInfoText.sprite.rect);

	SDL_RenderPresent(window.renderer);
}

void DetermineWindowStateFuncs() {
	if (window.state == STATE_BOXCOLOUR_R || window.state == STATE_BOXCOLOUR_G || window.state == STATE_BOXCOLOUR_B || window.state == STATE_BOXCOLOUR_A) {
		ChangeBoxColour(paintedRect, window.state);
		return;
	} if (window.state == STATE_SAVE_YN) {
		SaveData(rects, &infoText, infoString, saveFilename);
	} if (window.state == STATE_SAVEAS) {
		SaveDataAs(rects, &infoText, infoString, saveFilename);
	}
}

int main(int argc, char** argv) {
	if (argc < 5) {
		fprintf(stderr, "Usage: ./kuben <srcFile> <frameWidth> <frameHeight> <outFile>");
		return 1;
	}

	if (InitEverything(argv[1], atoi(argv[2]), atoi(argv[3]), argv[4]) == 1) return 1;


	imageDestRect = (SDL_Rect){0, 0, frameWidth * zoomFactor, frameHeight * zoomFactor};
	CenterHoriz(&imageDestRect, &(SDL_Rect){0, 0, window.width, window.height});
	CenterVert(&imageDestRect, &(SDL_Rect){0, 0, window.width, window.height});
	LoadData(rects, &infoText, infoString, saveFilename);
	while (WindowIsOpen()) {
		uint64_t timeStart = SDL_GetTicks64();

		// Clear
		SDL_SetRenderDrawColor(window.renderer, 0x4c, 0x00, 0xb0, 255);
		SDL_RenderClear(window.renderer);

		imageDestRect.w = frameWidth * zoomFactor;
		imageDestRect.h = frameHeight * zoomFactor;


		RedrawRect(rects, &paintedRect, zoomFactor);

		if (paintedRect) {
			snprintf(rectInfoString, 1000, "Rect dimensions = %d, %d, %d, %d\nIdentifier = %d\nColours: 0x%02x, 0x%02x, 0x%02x",
				(int)TransposeGridPixel((Vec2){paintedRect->rect.x, paintedRect->rect.y}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x,
				(int)TransposeGridPixel((Vec2){paintedRect->rect.x, paintedRect->rect.y}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y,
				(int)(TransposeGridPixel((Vec2){paintedRect->rect.w, paintedRect->rect.h}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x - TransposeGridPixel((Vec2){paintedRect->rect.x, paintedRect->rect.y}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).x),
				(int)(TransposeGridPixel((Vec2){paintedRect->rect.w, paintedRect->rect.h}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y - TransposeGridPixel((Vec2){paintedRect->rect.x, paintedRect->rect.y}, (float)zoomFactor * frameWidth / editSprite.rect.w, (float)zoomFactor * frameHeight / editSprite.rect.h, imageDestRect.x, imageDestRect.y).y),
			paintedRect->identifier, paintedRect->colour.r, paintedRect->colour.g, paintedRect->colour.b);
			boxInfoTextEmpty = false;
		} else {
			snprintf(rectInfoString, 2, " ");
			boxInfoTextEmpty = true;
		}
		CreateText(&boxInfoText, rectInfoString, 600, (SDL_Colour){255, 255, 255, 255});

		boxInfoText.sprite.rect.y = globalWindow->height - 75;
		
		if (window.state == STATE_NORMAL) {
			// Painting calculations
			PaintRectLit();

			// Frame jumping
			if (window.keys[SDL_SCANCODE_LEFT]) {
				ChangeFrame(&editSprite, frameWidth, frameHeight, -1);
			} if (window.keys[SDL_SCANCODE_RIGHT]) {
				ChangeFrame(&editSprite, frameWidth, frameHeight, 1);
			}
			
			HandlePanning(&editSprite, rects);

			// Recenter sprite
			if (window.keys[SDL_SCANCODE_RETURN]) {
				RecenterSprite(&editSprite, rects);
				ChangeBoxColour(NULL, 0);
			}

			if (window.keys[SDL_SCANCODE_DELETE]) {
				drawRect = true;
				paintedRect = NULL;
				for (int i = 0; i < 256; i++) {
					if (rects[i]) {
						free(rects[i]);
						*rects[i] = (Box){0};
						rects[i] = NULL;
					}
				}
			}

			if (window.keys[SDL_SCANCODE_F11]) {
				if (window.fullscreen == true) {
					SDL_SetWindowFullscreen(window.window, 0);
					window.width = 1280;
					window.height = 720;
					SDL_SetWindowSize(window.window, window.width, window.height);
					window.fullscreen = false;
				} else {
					SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
					SDL_GetWindowSize(window.window, &window.width, &window.height);
					window.fullscreen = true;
				}
			}

			// HandleZooming(&editSprite, rects);

			if (window.keys[SDL_SCANCODE_LCTRL] && window.keys[SDL_SCANCODE_S]) {
				if (window.keys[SDL_SCANCODE_LSHIFT])
					SaveDataAs(rects, &infoText, infoString, saveFilename);
				else
					SaveData(rects, &infoText, infoString, saveFilename);
			}
		} else {
			DetermineWindowStateFuncs();
		}

		Render();

		uint64_t timeEnd = SDL_GetTicks64();
		
		float timeElapsed = (timeEnd - timeStart) * 0.001;

		if (1000 / FPS > SDL_GetTicks64() - timeStart)
			SDL_Delay(1000 / FPS - timeElapsed);
	}
	DestroyEverything();
}
