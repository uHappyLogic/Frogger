#include "PipelineElements/PE_TimeProvider.hpp"


void PE_TimeProvider::Setup()
{
	currentTick = SDL_GetTicks();
}


void PE_TimeProvider::Execute()
{
	previousTick = currentTick;
	currentTick = SDL_GetTicks();
}


void PE_TimeProvider::Clean()
{

}


float PE_TimeProvider::getDeltaTime()
{
	return (this->previousTick - this->currentTick) * 0.001f;
}