#include "PipelineElements/PE_MovingBlock.hpp"
#include "SdlUtils.hpp"
#include <stdio.h>
#include "PipelineElements/PE_TimeProvider.hpp"


PE_MovingBlock::PE_MovingBlock(
	SDL_Surface * pictureSrc,
	int speed,
	bool movingLeft,
	SDL_Surface * screen,
	int currentPos_x,
	int currentPos_y,
	PE_TimeProvider* timeProvider,
	PE_Frog* frog)
	:
	screen(screen),
	currentPos_x(currentPos_x),
	currentPos_y(currentPos_y),
	timeProvider(timeProvider),
	movingLeft(movingLeft),
	speed(speed),
	pictureSrc(pictureSrc),
	frog(frog)
{

}

void PE_MovingBlock::Setup()
{

}

void PE_MovingBlock::Execute()
{
	float deltaX = speed * timeProvider->getDeltaTime();
	currentPos_x += (movingLeft ? -1 : 1) * (deltaX);

	DrawSurface(
		screen,
		pictureSrc,
		currentPos_x,
		currentPos_y);
}

void PE_MovingBlock::Clean()
{

}

CollidablePipelineElement::CollisionRect PE_MovingBlock::GetCollisionRect()
{
	auto rect = CollidablePipelineElement::CollisionRect();
	rect.width = pictureSrc->w;
	rect.height = pictureSrc->h;
	rect.x = currentPos_x;
	rect.y = currentPos_y;

	return rect;
}

void PE_MovingBlock::Collide(bool collide)
{
	if (collide)
	{
		frog->ResetToStartPosition();
	}
}