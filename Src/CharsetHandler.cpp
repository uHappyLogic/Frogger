#include "CharsetHandler.hpp"

#include <stdio.h>

CharsetHandler::CharsetHandler()
{
	charset = SDL_LoadBMP("./Assets/cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};
	SDL_SetColorKey(charset, true, 0x000000);
}

CharsetHandler::~CharsetHandler()
{
	SDL_FreeSurface(charset);
}