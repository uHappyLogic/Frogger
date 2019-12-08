#pragma once

#include "PipelineElement.h"

class PE_EventHandler : public PipelineElement
{
public:

	void Setup() override;

	void Execute() override;

	void Clean() override;

	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool escape = false;
	bool appExit = false;
};