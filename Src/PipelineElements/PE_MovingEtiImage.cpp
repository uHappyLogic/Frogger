#include "PipelineElements/PE_MovingEtiImage.hpp"
#include "SdlUtils.hpp"
#include <stdio.h>
#include "PipelineElements/PE_TimeProvider.hpp"


PE_MovingEtiImage::PE_MovingEtiImage(
	SDL_Surface * screen,
	int screenWidth,
	int screenHeigh, 
	PE_TimeProvider* timeProvider)
	:screen (screen), screenWidth(screenWidth), screenHeigh(screenHeigh), timeProvider(timeProvider)
{
	
}

void PE_MovingEtiImage::Setup()
{
	eti = SDL_LoadBMP("./Assets/eti.bmp");
	if (eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

}

void PE_MovingEtiImage::Execute()
{
	
	distance += etiSpeed * timeProvider->getDeltaTime();
	DrawSurface(
		screen,
		eti,
		screenWidth / 2 + sin(distance) * screenHeigh / 3,
		screenHeigh / 2 + cos(distance) * screenHeigh / 3);

}

void PE_MovingEtiImage::Clean()
{

}