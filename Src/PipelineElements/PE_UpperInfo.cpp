#include "PipelineElements/PE_UpperInfo.hpp"

#include <stdio.h>
#include <string.h>

#include "SdlUtils.hpp"


PE_UpperInfo::PE_UpperInfo(
	SDL_Surface * screen,
	int screenWidth,
	int screenHeight,
	SDL_Surface *charset,
	PE_TimeProvider* timeProvider)
	: screen(screen),
	screenWidth(screenWidth),
	screenHeight(screenHeight),
	charset(charset),
	timeProvider(timeProvider)
{

}

void PE_UpperInfo::Setup()
{
	redColor = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blueColor = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}


void PE_UpperInfo::Execute()
{
	++frames;
	worldTime += timeProvider->getDeltaTime();

	fpsTimer += timeProvider->getDeltaTime();
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};

	// tekst informacyjny / info text
	DrawRectangle(
		screen, 4, 4, screenWidth - 8, 36, redColor, blueColor
	);

	//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"		
	sprintf(
		text,
		"Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s",
		worldTime,
		fps);

	DrawString(
		screen,
		screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset
	);
	//	      "Esc - exit, \030 - faster, \031 - slower"
	sprintf(text, "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
	DrawString(
		screen,
		screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset
	);
}


void PE_UpperInfo::Clean()
{

}