#pragma once

#include "PipelineElement.h"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_EventHandler.hpp"


class PE_Frog : public PipelineElement
{
public:

	PE_Frog(
		SDL_Surface* pictureSrc,
		SDL_Surface * screen,
		int screenWidth,
		int screenHeigh,
		PE_TimeProvider* timeProvider,
		PE_EventHandler* eventHandler);

	void Setup() override;

	void Execute() override;

	void Clean() override;

	float GetCenterX();

	float GetCenterY();

	void ResetToStartPosition();

private:
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float screenWidth;
	float screenHeigh;
	PE_TimeProvider* timeProvider;
	float distance = 0;
	PE_EventHandler* eventHandler;
	float currentPosX;
	float currentPosY;
	float startPosX;
	float startPosY;
};