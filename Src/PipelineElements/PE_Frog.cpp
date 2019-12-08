#include "PipelineElements/PE_Frog.hpp"
#include "SdlUtils.hpp"
#include <stdio.h>
#include "PipelineElements/PE_TimeProvider.hpp"


PE_Frog::PE_Frog(
	SDL_Surface * pictureSrc,
	SDL_Surface * screen,
	int screenWidth,
	int screenHeigh,
	PE_TimeProvider* timeProvider)
	:screen(screen), screenWidth(screenWidth), screenHeigh(screenHeigh), timeProvider(timeProvider), pictureSrc(pictureSrc)
{

}

void PE_Frog::Setup()
{

}

void PE_Frog::Execute()
{
	
	int currentPos_x = screenWidth/2;
	int currentPos_y = screenHeigh-16;

	DrawSurface(
		screen,
		pictureSrc,
		currentPos_x,
		currentPos_y);
}

void PE_Frog::Clean()
{

}