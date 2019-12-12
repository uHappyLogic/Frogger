#pragma once

#include "SdlUtils.hpp"

class SdlContextHandler
{
public:

    enum Mode
    {
        WINDOWED,
        FULLSCREEN
    };

    SdlContextHandler(int width, int height, Mode mode);

    ~SdlContextHandler();

    void DrawScreen(SDL_Surface *screen);

private:

    int rc;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
};