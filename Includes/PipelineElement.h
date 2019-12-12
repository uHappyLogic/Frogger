#pragma once

extern "C" {
#include"Sdl/SDL.h"
}

#include "SdlScreenHandler.h"

class PipelineElement
{
public:

	// This method is called once at the beginning ofthe game
	virtual void Setup() = 0;

	// This method is called once every
	virtual void Execute() = 0;

	// This method is called once just before exit
	virtual void Clean() = 0;

	virtual ~PipelineElement(){ }
};