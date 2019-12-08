#include "PipelineElements/PE_QuitHandler.hpp"
#include <stdio.h>

PE_QuitHandler::PE_QuitHandler(
	PE_EventHandler* eventHandler)
	: eventHandler(eventHandler)
{

}

bool PE_QuitHandler::ShouldQuit()
{
	return eventHandler->escape || eventHandler->appExit;
}