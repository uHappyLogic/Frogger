#pragma once

#include "PipelineElement.h"
#include "SdlScreenHandler.h"

class PipelineElementManager
{
public:

	PipelineElementManager(SdlScreenHandler *sdlScreenHandler);

	void AddPipeline(PipelineElement* element);

	void Init();

	void RunAllElements();

	~PipelineElementManager();

private:

	struct Node
	{
		PipelineElement* element;
		Node* next;

		~Node();
	};

	Node* head = nullptr;
	SdlScreenHandler *sdlScreenHandler;
};