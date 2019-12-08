#pragma once

#include "PipelineElement.h"


class PE_TimeProvider : public PipelineElement
{
public:

	float getDeltaTime();

	void Setup() override;

	void Execute() override;

	void Clean() override;

private:

	int previousTick;
	int currentTick;
};