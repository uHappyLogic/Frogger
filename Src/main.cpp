#include<stdio.h>
#include<string.h>

#include "CharsetHandler.hpp"
#include "CollidableManager.hpp"
#include "PipelineElementManager.h"
#include "SdlContextHandler.hpp"
#include "SdlScreenHandler.h"
#include "SdlUtils.hpp"
#include "TextureHandler.hpp"

#include "PipelineElements/PE_Background.hpp"
#include "PipelineElements/PE_EventHandler.hpp"
#include "PipelineElements/PE_Frog.hpp"
#include "PipelineElements/PE_MovingBlock.hpp"
#include "PipelineElements/PE_QuitHandler.hpp"
#include "PipelineElements/PE_River.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_UpperInfo.hpp"


int main(int argc, char **argv) {

	/*
	 * ======================================================================================================================
	 *												   SDL Init
	 * ======================================================================================================================
	 */

	#define SCREEN_WIDTH	640
	#define SCREEN_HEIGHT	480

	SdlContextHandler sdlContextHandler(
		SCREEN_WIDTH, SCREEN_HEIGHT, SdlContextHandler::WINDOWED);

	auto sdlScreenHandler = SdlScreenHandler(SCREEN_WIDTH, SCREEN_HEIGHT);

	/*
	 * ======================================================================================================================
	 *												Assets loading
	 * ====================================================================================================================== 
	 */

	auto carBmp = TextureHandler("./Assets/greenCar.bmp");
	auto frogBmp = TextureHandler("./Assets/frog1.bmp");
	auto planckBmp = TextureHandler("./Assets/block.bmp");
	auto riverBmp = TextureHandler("./Assets/river.bmp");
	auto roadBmp = TextureHandler("./Assets/road.bmp");

	/*
	 * ======================================================================================================================
	 *												Rows Y generation
	 * ======================================================================================================================
	 */

	int rows[15];
	for (int i = 0; i < 480 / 32; i++)
	{
		rows[i] = ((480 - (i * 32)) - 16);
	}

	/*
	 * ======================================================================================================================
	 *												Scene setup
	 * ======================================================================================================================
	 */

	auto timeProvider = new PE_TimeProvider();
	auto charsetHandler = CharsetHandler();

	auto eventHandler = new PE_EventHandler();

	auto frog = new PE_Frog(frogBmp.texture, sdlScreenHandler.screen, SCREEN_WIDTH, SCREEN_HEIGHT, timeProvider, eventHandler);

	auto collidableManager = CollidableManager(frog);

	auto quitHandler = PE_QuitHandler(eventHandler);

	auto pipeline = PipelineElementManager(
		&collidableManager
	);

	pipeline.AddElement(
		eventHandler
	);

	pipeline.AddElement(
		new PE_Background(sdlScreenHandler.screen)
	);

	pipeline.AddElement(
		timeProvider
	);

	pipeline.AddElement(
		new PE_MovingBlock(roadBmp.texture, 0, true, sdlScreenHandler.screen, SCREEN_WIDTH / 2, rows[4] + 16, timeProvider, frog, action_options::NOTHING, 9)
	);

	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH + 160, rows[6], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30,false,sdlScreenHandler.screen, SCREEN_WIDTH+60, rows[5], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30, true, sdlScreenHandler.screen, -100, rows[4], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[3], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);
	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30, true, sdlScreenHandler.screen, 0, rows[2], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);

	pipeline.AddElement(
		new PE_MovingBlock(carBmp.texture, 30, true, sdlScreenHandler.screen, -40, rows[1], timeProvider, frog, action_options::MOVE_TO_START, 5)
	);

	pipeline.AddElement(
		new PE_River(riverBmp.texture, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[8], timeProvider,true, frog, 9)
	);
	pipeline.AddElement(
		new PE_River(riverBmp.texture, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[9], timeProvider, false, frog, 9)
	);

	pipeline.AddElement(
		new PE_River(riverBmp.texture, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[10], timeProvider, true, frog, 9)
	);

	pipeline.AddElement(
		new PE_River(riverBmp.texture, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[11], timeProvider, false, frog, 9)
	);
	pipeline.AddElement(
		new PE_River(riverBmp.texture, 10, sdlScreenHandler.screen, SCREEN_WIDTH, rows[12], timeProvider, true, frog, 9)
	);

	pipeline.AddElement(
		new PE_MovingBlock(planckBmp.texture, 30, true, sdlScreenHandler.screen, 0, rows[8], timeProvider, frog, action_options::DRAG, 5)
	);
	
	pipeline.AddElement(
		new PE_MovingBlock(planckBmp.texture, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[9], timeProvider, frog, action_options::DRAG, 5)
	);
	
	pipeline.AddElement(
		new PE_MovingBlock(planckBmp.texture, 30, true, sdlScreenHandler.screen, 0, rows[10], timeProvider, frog, action_options::DRAG, 5)
	);
	
	pipeline.AddElement(
		new PE_MovingBlock(planckBmp.texture, 30, false, sdlScreenHandler.screen, SCREEN_WIDTH, rows[11], timeProvider, frog, action_options::DRAG, 5)
	);
	
	pipeline.AddElement(
		new PE_MovingBlock(planckBmp.texture, 30, true, sdlScreenHandler.screen, 0, rows[12], timeProvider, frog, action_options::DRAG, 5)
	);

	pipeline.AddElement(
		frog
	);

	pipeline.AddElement(
		new PE_UpperInfo(
			sdlScreenHandler.screen,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			charsetHandler.charset,
			timeProvider
		)
	);

	/*
	 * ======================================================================================================================
	 *													Main game loop
	 * ======================================================================================================================
	 */

	pipeline.Init();

	while(!quitHandler.ShouldQuit())
	{
		// Run logic of all registered elements
		pipeline.RunAllElements();

		// Draw
		sdlContextHandler.DrawScreen(sdlScreenHandler.screen);

		// check collisions
		collidableManager.TriggerCollision();
	};

	/*
	 * ======================================================================================================================
	 *													     Exit
	 *		    On exit all destructors are run, thus all resources attached to e.g. TextureHandlers are freed
	 * ======================================================================================================================
	 */

	return 0;
};
