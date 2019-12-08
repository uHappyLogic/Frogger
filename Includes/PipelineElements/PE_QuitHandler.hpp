#pragma once

#include "PipelineElement.h"
#include "SdlScreenHandler.h"
class PE_QuitHandler : public PipelineElement 
{
public:

	PE_QuitHandler();

	void Setup() override;

	void Execute() override;

	void Clean() override;
 
	bool shouldQuit = false;

};
