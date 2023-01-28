#include "Text.h"

void LoadText(Text* text, int fontSize, char* srcFilename) {
	text->font = TTF_OpenFont(srcFilename, fontSize);
}

void CreateText(Text* text, char* textLit, int wrapWidth, SDL_Colour colour) {
	SDL_Surface* surf = TTF_RenderUTF8_Blended_Wrapped(text->font, textLit, colour, wrapWidth);
	text->sprite.width = text->sprite.rect.w = surf->w;
	text->sprite.height = text->sprite.rect.h = surf->h;
	text->sprite.bitmap = SDL_CreateTextureFromSurface(globalWindow->renderer, surf);

	SDL_FreeSurface(surf);
}