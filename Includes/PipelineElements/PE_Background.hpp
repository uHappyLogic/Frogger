#pragma once

#include "PipelineElement.h"
#include "SdlScreenHandler.h"


class PE_Background : public PipelineElement
{
public:

	PE_Background(SDL_Surface* screen);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:

	int backgroundColor;
	SDL_Surface* screen;
};