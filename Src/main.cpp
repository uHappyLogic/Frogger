#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "SdlUtils.hpp"
#include "SdlScreenHandler.h"
#include "PipelineElementManager.h"
#include "CharsetHandler.hpp"
#include "CollidableManager.hpp"

#include "PipelineElements/PE_Background.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_UpperInfo.hpp"
#include "PipelineElements/PE_QuitHandler.hpp"
#include "PipelineElements/PE_EventHandler.hpp"
#include "PipelineElements/PE_MovingBlock.hpp"
#include "PipelineElements/PE_Frog.hpp"
#include "PipelineElements/PE_River.hpp"



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

	auto carBmp = SDL_LoadBMP("./Assets/greenCar.bmp");
	auto frogBmp = SDL_LoadBMP("./Assets/frog1.bmp");
	auto planckBmp = SDL_LoadBMP("./Assets/block.bmp");
	auto riverBmp = SDL_LoadBMP("./Assets/river.bmp");
	auto roadBmp = SDL_LoadBMP("./Assets/road.bmp");

	if (carBmp == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	if (roadBmp == NULL) {
		printf("SDL_LoadBMP(road.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	if (frogBmp == NULL) {
		printf("SDL_LoadBMP(frog1.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	if (planckBmp == NULL) {
		printf("SDL_LoadBMP(block.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};
	if (riverBmp == NULL) {
		printf("SDL_LoadBMP(river.bmp) error: %s\n", SDL_GetError());
		SDL_Quit();
	};

	auto sdlScreenHandler = SdlScreenHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto timeProvider = new PE_TimeProvider();
	auto charsetHandler = CharsetHandler();

	auto eventHandler = new PE_EventHandler();

	auto frog = new PE_Frog(frogBmp, sdlScreenHandler.screen, SCREEN_WIDTH, SCREEN_HEIGHT, timeProvider, eventHandler);

	auto collidableManager = CollidableManager(frog);

	auto quitHandler = PE_QuitHandler(eventHandler);

	auto graphicsPipelineManager = PipelineElementManager(
		&collidableManager
	);

	graphicsPipelineManager.AddPipeline(
		eventHandler
	);

	graphicsPipelineManager.AddPipeline(
		new PE_Background(sdlScreenHandler.screen)
	);

	graphicsPipelineManager.AddPipeline(
		timeProvider
	);

	/*graphicsPipelineManager.AddPipeline(
		new PE_MovingEtiImage(sdlScreenHandler.screen,SCREEN_WIDTH,SCREEN_HEIGHT, & timeProvider)
	);
	*/
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(roadBmp, 0, true, sdlScreenHandler.screen, SCREEN_WIDTH / 2, rows[4] + 16, timeProvider, frog, action_options::NOTHING, 9)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH + 160, rows[6], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30,false,sdlScreenHandler.screen, SCREEN_WIDTH+60, rows[5], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, -100, rows[4], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[3], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, 0, rows[2], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, -40, rows[1], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_River(riverBmp, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[8], timeProvider,true, frog, 9)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_River(riverBmp, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[9], timeProvider, false, frog, 9)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_River(riverBmp, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[10], timeProvider, true, frog, 9)
	);

	graphicsPipelineManager.AddPipeline(
		new PE_River(riverBmp, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[11], timeProvider, false, frog, 9)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_River(riverBmp, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[12], timeProvider, true, frog, 9)
	);
	graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, 0, rows[8], timeProvider, frog, action_options::DRAG, 5)
	); graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[9], timeProvider, frog, action_options::DRAG, 5)
	); graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, 0, rows[10], timeProvider, frog, action_options::DRAG, 5)
	); graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[11], timeProvider, frog, action_options::DRAG, 5)
	); graphicsPipelineManager.AddPipeline(
		new PE_MovingBlock(carBmp, 30, true, sdlScreenHandler.screen, 0, rows[12], timeProvider, frog, action_options::DRAG, 5)
	);

	graphicsPipelineManager.AddPipeline(
		frog
	);

	graphicsPipelineManager.AddPipeline(
		new PE_UpperInfo(
			sdlScreenHandler.screen,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			charsetHandler.charset,
			timeProvider
		)
	);

	graphicsPipelineManager.Init();

	while(!quitHandler.ShouldQuit()) {
		graphicsPipelineManager.RunAllElements();

		SDL_UpdateTexture(
			scrtex, NULL, sdlScreenHandler.screen->pixels, sdlScreenHandler.screen->pitch);

		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		collidableManager.TriggerCollision();
	};

	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
