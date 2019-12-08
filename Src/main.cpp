#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

#include "SdlUtils.hpp"
#include "SdlScreenHandler.h"
#include "PipelineElementManager.h"

#include "PipelineElements/PE_Background.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_MovingEtiImage.hpp"
#include "PipelineElements/PE_QuitHandler.hpp"


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

int main(int argc, char **argv) {
	int t1, t2, quit, frames, rc;
	double worldTime, fpsTimer, fps, distance, etiSpeed;
	SDL_Event event;
	SDL_Surface *charset;
	
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// okno konsoli nie jest widoczne, jeżeli chcemy zobaczyć
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmienić na "Console"
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

	// tryb pełnoekranowy / fullscreen mode
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

	// wyłączenie widoczności kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./Assets/cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	
	char text[128];

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;

	auto sdlScreenHandler = SdlScreenHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	auto timeProvider = PE_TimeProvider();

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


	graphicsPipelineManager.Init();

	int zielony = SDL_MapRGB(sdlScreenHandler.screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(sdlScreenHandler.screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(sdlScreenHandler.screen->format, 0x11, 0x11, 0xCC);


	while(!quitHandler.shouldQuit) {
		graphicsPipelineManager.RunAllElements();

		worldTime += timeProvider.getDeltaTime();

		

		
		fpsTimer += timeProvider.getDeltaTime();
		if(fpsTimer > 0.5) {
			fps = frames * 2;
			frames = 0;
			fpsTimer -= 0.5;
			};

		// tekst informacyjny / info text
		DrawRectangle(
			sdlScreenHandler.screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski
		);
		
		//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"		
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		
		DrawString(
			sdlScreenHandler.screen,
			sdlScreenHandler.screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset
		);
		//	      "Esc - exit, \030 - faster, \031 - slower"
		sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
		DrawString(
			sdlScreenHandler.screen,
			sdlScreenHandler.screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset
		);

		SDL_UpdateTexture(
			scrtex, NULL, sdlScreenHandler.screen->pixels, sdlScreenHandler.screen->pitch);

//		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);		
		frames++;
		};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
