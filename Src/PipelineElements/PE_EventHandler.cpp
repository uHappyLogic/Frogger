#include "PipelineElements/PE_EventHandler.hpp"

#include <cstdio>

void PE_EventHandler::Setup()
{

}

void PE_EventHandler::Execute()
{
	left = false;
	right = false;
	up = false;
	down = false;
	escape = false;
	appExit = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			printf("key pressed");
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				escape = true;
			}
			else if(event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
			{
				up = true;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
			{
				down = true;
			}
			else if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
			{
				left = true;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
			{
				right = true;
			}

			continue;
		case SDL_QUIT:
			appExit = true;
			continue;
		};
	};
}

void PE_EventHandler::Clean()
{

}