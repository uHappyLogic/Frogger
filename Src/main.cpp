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
#include "PipelineElements/PE_EventHandler.hpp"
#include "PipelineElements/PE_MovingBlock.hpp"
#include "PipelineElements/PE_Frog.hpp"



#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

int main(int argc, char **argv) {
	int quit, rc;
	SDL_Event event;
	
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	float etiSpeed;
	int rows[15];
	for (int i = 0; i < 480/32; i++)
	{
		rows[i] = ((480 - (i * 32)) - 16);
	}

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

	auto carBmp = SDL_LoadBMP("./Assets/eti.bmp");
	auto frogBmp = SDL_LoadBMP("./Assets/frog1.bmp");
	auto planckBmp = SDL_LoadBMP("./Assets/block.bmp");

	if (carBmp == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	if (frogBmp == NULL) {
		printf("SDL_LoadBMP(frog1.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	if (frogBmp == NULL) {
		printf("SDL_LoadBMP(block.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	auto sdlScreenHandler = SdlScreenHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto timeProvider = PE_TimeProvider();
	auto charsetHandler = CharsetHandler();

	auto eventHandler = PE_EventHandler();

	auto quitHandler = PE_QuitHandler(&eventHandler);

	auto graphicsPipelineManager = PipelineElementManager(
		&sdlScreenHandler	
	);

	graphicsPipelineManager.AddPipeline(
		&eventHandler
	);

	graphicsPipelineManager.AddPipeline(
		new PE_Background(sdlScreenHandler.screen)
	);

	graphicsPipelineManager.AddPipeline(
		&timeProvider
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingEtiImage(sdlScreenHandler.screen,SCREEN_WIDTH,SCREEN_HEIGHT, & timeProvider)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30,false,sdlScreenHandler.screen, SCREEN_WIDTH, SCREEN_HEIGHT/4, &timeProvider)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(planckBmp, 30,true, sdlScreenHandler.screen, -20, rows[1], &timeProvider)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_Frog(frogBmp,  sdlScreenHandler.screen, SCREEN_WIDTH, SCREEN_HEIGHT, &timeProvider)
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

	while(!quitHandler.ShouldQuit()) {
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
