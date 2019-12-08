#pragma once

#include "PipelineElement.h"

#include "PipelineElements/PE_TimeProvider.hpp"


class PE_UpperInfo : public PipelineElement
{
public:

	PE_UpperInfo(
		SDL_Surface * screen,
		int screenWidth,
		int screenHeight,
		SDL_Surface *charset,
		PE_TimeProvider* timeProvider
	);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:

	SDL_Surface * screen;
	int screenWidth;
	int screenHeight;
	int redColor;
	int blueColor;
	SDL_Surface *charset;
	char text[128];
	float worldTime = 0;
	PE_TimeProvider* timeProvider;
	float fpsTimer = 0.0f;
	float fps = 0.0f;
	int frames = 0;
};