#include "PipelineElement.h"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_EventHandler.hpp"


class PE_River : public PipelineElement
{
public:

	PE_River(
		SDL_Surface* pictureSrc,
		int speed,
		SDL_Surface * screen,
		int screenWidth,
		int screenHeigh,
		PE_TimeProvider* timeProvider,
		bool movingRight
		);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:
	bool movingRight;
	int speed;
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float screenWidth;
	float screenHeigh;
	PE_TimeProvider* timeProvider;
	float distance = 0;
	float currentPosX;
	float currentPosY;
};