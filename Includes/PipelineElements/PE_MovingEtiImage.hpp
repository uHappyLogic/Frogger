#pragma once
#include "PipelineElement.h"
#include "PipelineElements/PE_TimeProvider.hpp"


class PE_MovingEtiImage : public PipelineElement 
{
public:

	PE_MovingEtiImage(
		SDL_Surface * screen,
		int  screenWidth,
		int screenHeigh,
		PE_TimeProvider* timeProvider);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:
	SDL_Surface* screen;
	SDL_Surface *eti;
	int screenWidth;
	int screenHeigh;
	float etiSpeed = 1.0f;
	PE_TimeProvider* timeProvider;
	float distance = 0;
};