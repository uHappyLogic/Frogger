#pragma once

#include "CollidablePipelineElement.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_Frog.hpp"


namespace action_options
{
	enum ActionOptions
	{
		NOTHING,
		MOVE_TO_START,
		DRAG
	};
}

class PE_MovingBlock : public CollidablePipelineElement
{
public:

	PE_MovingBlock(
		SDL_Surface* pictureSrc,
		int speed,
		bool movingLeft,
		SDL_Surface * screen,
		int  currentPos_x,
		int currentPos_y,
		PE_TimeProvider* timeProvider,
		PE_Frog* frog,
		action_options::ActionOptions ap);

	void Setup() override;

	void Execute() override;

	void Clean() override;

	CollisionRect GetCollisionRect();

	bool Collide(bool collide);

private:
	int speed;
	bool movingLeft = false;
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float currentPos_x;
	float currentPos_y;
	PE_TimeProvider* timeProvider;
	float distance = 0;
	PE_Frog* frog;
	action_options::ActionOptions ap;
};