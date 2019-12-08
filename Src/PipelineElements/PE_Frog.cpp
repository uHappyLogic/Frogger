#include "PipelineElements/PE_Frog.hpp"
#include "SdlUtils.hpp"
#include <stdio.h>
#include "PipelineElements/PE_TimeProvider.hpp"


PE_Frog::PE_Frog(
	SDL_Surface * pictureSrc,
	SDL_Surface * screen,
	int screenWidth,
	int screenHeigh,
	PE_TimeProvider* timeProvider,
	PE_EventHandler* eventHandler
) :
	screen(screen),
	screenWidth(screenWidth),
	screenHeigh(screenHeigh),
	timeProvider(timeProvider),
	pictureSrc(pictureSrc),
	eventHandler(eventHandler)
{

}

void PE_Frog::Setup()
{
	currentPosX = screenWidth / 2;
	currentPosY = screenHeigh - 16;

}

void PE_Frog::Execute()
{
	if (eventHandler->up)
		currentPosY -= 32;
	if (eventHandler->down)
		currentPosY += 32;
	if (eventHandler->left)
		currentPosX -= 32;
	if (eventHandler->right)
		currentPosX += 32;
	
	DrawSurface(
		screen,
		pictureSrc,
		currentPosX,
		currentPosY);
}

void PE_Frog::Clean()
{

}