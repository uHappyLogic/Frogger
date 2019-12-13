#pragma once

#include "SdlUtils.hpp"

#include <string>
#include <cstdio>


class TextureHandler
{
public:

	TextureHandler(std::string path)
	{
		texture = SDL_LoadBMP(path.c_str());

		if (texture == NULL) {
			printf("SDL_LoadBMP(%s) error: %s\n", path.c_str(), SDL_GetError());
			SDL_Quit();
		};
	}

	~TextureHandler()
	{
		SDL_FreeSurface(texture);
	}

	SDL_Surface* texture;
};