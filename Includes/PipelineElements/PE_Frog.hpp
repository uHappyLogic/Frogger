#include "PipelineElement.h"
#include "PipelineElements/PE_TimeProvider.hpp"


class PE_Frog : public PipelineElement
{
public:

	PE_Frog(
		SDL_Surface* pictureSrc,
		SDL_Surface * screen,
		int screenWidth,
		int screenHeigh,
		PE_TimeProvider* timeProvider);

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float screenWidth;
	float screenHeigh;
	PE_TimeProvider* timeProvider;
	float distance = 0;
};