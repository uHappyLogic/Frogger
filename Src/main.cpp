#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "SdlUtils.hpp"
#include "SdlScreenHandler.h"
#include "PipelineElementManager.h"
#include "CharsetHandler.hpp"

#include "PipelineElements/PE_Background.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_MovingEtiImage.hpp"
#include "PipelineElements/PE_UpperInfo.hpp"
#include "PipelineElements/PE_QuitHandler.hpp"


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

int main(int argc, char **argv) {
	int quit, rc;
	SDL_Event event;
	
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	float etiSpeed;

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
		return 1;
		}

	// tryb pe�noekranowy / fullscreen mode
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	quit = 0;

	auto sdlScreenHandler = SdlScreenHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto timeProvider = PE_TimeProvider();
	auto charsetHandler = CharsetHandler();

	auto quitHandler = PE_QuitHandler();

	auto graphicsPipelineManager = PipelineElementManager(
		&sdlScreenHandler	
	);

	graphicsPipelineManager.AddPipeline(
		new PE_Background(sdlScreenHandler.screen)
	);

	graphicsPipelineManager.AddPipeline(
		&timeProvider
	);

	graphicsPipelineManager.AddPipeline(
		&quitHandler
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingEtiImage(sdlScreenHandler.screen,SCREEN_WIDTH,SCREEN_HEIGHT, & timeProvider)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_UpperInfo(
			sdlScreenHandler.screen,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			charsetHandler.charset,
			&timeProvider
		)
	);

	graphicsPipelineManager.Init();

	while(!quitHandler.shouldQuit) {
		graphicsPipelineManager.RunAllElements();

		SDL_UpdateTexture(
			scrtex, NULL, sdlScreenHandler.screen->pixels, sdlScreenHandler.screen->pitch);

		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);		
	};

	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
