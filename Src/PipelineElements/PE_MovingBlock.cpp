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
	PE_Frog* frog,
	action_options::ActionOptions ap,
	int layer)
	:
	screen(screen),
	currentPos_x(currentPos_x),
	currentPos_y(currentPos_y),
	timeProvider(timeProvider),
	movingLeft(movingLeft),
	speed(speed),
	pictureSrc(pictureSrc),
	frog(frog),
	ap(ap),
	layer(layer)
{

}

void PE_MovingBlock::Setup()
{

}

void PE_MovingBlock::Execute()
{
	float deltaX = speed * timeProvider->getDeltaTime();
	this->currentDrag = (movingLeft ? -1 : 1) * (deltaX);
	currentPos_x += this->currentDrag;

	// element cycling logic
	if (currentPos_x >  2 * screen->w)
		currentPos_x = -pictureSrc->w;
	else if (currentPos_x < -pictureSrc->w)
		currentPos_x = 2 * screen->w;

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
		switch (ap)
		{
		case action_options::NOTHING:
			break;
		case action_options::MOVE_TO_START:
			this->frog->ResetToStartPosition();
			printf("Moving to start position\n");
			break;
		case action_options::DRAG:
			this->frog->dragHorizontaly(this->currentDrag);
			break;
		default:
			break;
		}
	}
}

int PE_MovingBlock::GetPriority()
{
	return layer;
}