#include "SdlScreenHandler.h"

SdlScreenHandler::SdlScreenHandler(int width, int height)
{
	this->screen = SDL_CreateRGBSurface(0, width, height, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
}

SdlScreenHandler::SdlScreenHandler()
{
	SDL_FreeSurface(this->screen);
}