#include "PipelineElements/PE_River.hpp"
#include "SdlUtils.hpp"
#include <stdio.h>
#include "PipelineElements/PE_TimeProvider.hpp"


PE_River::PE_River(
	SDL_Surface * pictureSrc,
	int speed,
	SDL_Surface * screen,
	int screenWidth,
	int screenHeigh,
	PE_TimeProvider* timeProvider,
	bool movingRight
) :
	screen(screen),
	screenWidth(screenWidth),
	screenHeigh(screenHeigh),
	timeProvider(timeProvider),
	pictureSrc(pictureSrc),
	speed(speed),
	movingRight(movingRight)
	
{

}

void PE_River::Setup()
{
	currentPosX = screenWidth / 2;
	currentPosY = screenHeigh;

}

void PE_River::Execute()
{
	if (currentPosX>=336)
	{
		movingRight = true;
	} else if(currentPosX <= 304)
		{
		movingRight = false;
		}
	float deltaX = speed * timeProvider->getDeltaTime();
	currentPosX += (movingRight ? +1 : -1) * (deltaX);
	DrawSurface(
		screen,
		pictureSrc,
		currentPosX,
		currentPosY);
}

void PE_River::Clean()
{

}