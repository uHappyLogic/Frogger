#include "PipelineElement.h"
#include "PipelineElements/PE_TimeProvider.hpp"


class PE_MovingBlock : public PipelineElement
{
public:

	PE_MovingBlock(
		SDL_Surface* pictureSrc,
		int speed,
		bool movingLeft,
		SDL_Surface * screen,
		int  currentPos_x,
		int currentPos_y,
		PE_TimeProvider* timeProvider);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:
	int speed;
	bool movingLeft = false;
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float currentPos_x;
	float currentPos_y;
	PE_TimeProvider* timeProvider;
	float distance = 0;
};