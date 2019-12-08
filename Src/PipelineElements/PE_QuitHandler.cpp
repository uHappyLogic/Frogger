#include "PipelineElements/PE_QuitHandler.hpp"
#include <stdio.h>

PE_QuitHandler::PE_QuitHandler()
{

}

void PE_QuitHandler::Setup()
{

}

void PE_QuitHandler::Execute()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			printf("key pressed");
			if (event.key.keysym.sym == SDLK_ESCAPE) shouldQuit = true;
			continue;
		case SDL_QUIT:
			shouldQuit = true;
			break;
		};
	};

	
}

void PE_QuitHandler::Clean()
{

}