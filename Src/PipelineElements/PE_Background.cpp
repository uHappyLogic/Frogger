#include "PipelineElements/PE_Background.hpp"


PE_Background::PE_Background(SDL_Surface* screen)
	: screen(screen)
{

}

void PE_Background::Setup()
{
	// backgroundColor = SDL_MapRGB(screen.format, 0x00, 0x00, 0x00);
	backgroundColor = SDL_MapRGB(
		this->screen->format, 0x11, 0x11, 0xCC);
}

void PE_Background::Execute()
{
	SDL_FillRect(this->screen, NULL, backgroundColor);
}

void PE_Background::Clean()
{

}