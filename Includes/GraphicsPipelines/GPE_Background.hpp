#pragma once

#include "GraphicsPipelineElement.h"
#include "SdlScreenHandler.h"


class GPE_Background : public GraphicsPipelineElement
{
public:

	void Setup(SDL_Surface& screen) override;

	void Draw(SDL_Surface& screen, const float time_delta) override;

	void Clean() override;

private:

	int backgroundColor;
};