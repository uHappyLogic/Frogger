#pragma once

#include "SdlScreenHandler.h"

#include "PipelineElements/PE_EventHandler.hpp"

class PE_QuitHandler
{
public:

	PE_QuitHandler(PE_EventHandler* eventHandler);
 
	bool ShouldQuit();

	PE_EventHandler* eventHandler;
};
