#include "SdlContextHandler.hpp"

#include <cstdio>

SdlContextHandler::SdlContextHandler(int width, int height, Mode mode)
{
	// okno konsoli nie jest widoczne, je�eli chcemy zobaczy�
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieni� na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
	}

	if (mode == FULLSCREEN)
	{
		rc = SDL_CreateWindowAndRenderer(
			0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer);
	}
	else
	{
		rc = SDL_CreateWindowAndRenderer(
			width, height, 0, &window, &renderer);
	}

	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, width, height);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Frogger");

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           width, height);

	SDL_ShowCursor(SDL_DISABLE);
}

SdlContextHandler::~SdlContextHandler()
{
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void SdlContextHandler::DrawScreen(SDL_Surface *screen)
{
		SDL_UpdateTexture(
			this->scrtex,
			NULL,
			screen->pixels,
			screen->pitch
		);

		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
}