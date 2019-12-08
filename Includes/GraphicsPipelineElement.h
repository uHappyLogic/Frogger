#pragma once

extern "C" {
#include"Sdl/SDL.h"
}

#include "SdlScreenHandler.h"

class GraphicsPipelineElement
{
public:

	// This method is called once at the beginning ofthe game
	virtual void Setup(SDL_Surface& screen) = 0;

	// This method is called once every frame after logic pipeline
	virtual void Draw(SDL_Surface& screen, const float time_delta) = 0;

	// This method is called once just before exit
	virtual void Clean() = 0;
};