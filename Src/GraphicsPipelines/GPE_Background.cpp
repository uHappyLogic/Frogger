#include "GraphicsPipelines/GPE_Background.hpp"

void GPE_Background::Setup(SDL_Surface& screen)
{
	// backgroundColor = SDL_MapRGB(screen.format, 0x00, 0x00, 0x00);
	backgroundColor = SDL_MapRGB(screen.format, 0x11, 0x11, 0xCC);
}

void GPE_Background::Draw(SDL_Surface& screen, const float time_delta)
{
	SDL_FillRect(&screen, NULL, backgroundColor);
}

void GPE_Background::Clean()
{

}