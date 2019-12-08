#pragma once

extern "C" {
#include"Sdl/SDL.h"
}


class SdlScreenHandler
{
public:

	SdlScreenHandler(int width, int height);

	SdlScreenHandler();

	SDL_Surface *screen;
};