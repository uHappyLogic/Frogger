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