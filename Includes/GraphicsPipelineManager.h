#pragma once

#include "GraphicsPipelineElement.h"
#include "SdlScreenHandler.h"

class GraphicsPipelineManager
{
public:

	GraphicsPipelineManager(SdlScreenHandler *sdlScreenHandler);

	void AddPipeline(GraphicsPipelineElement* element);

	void Init();

	void RunAllElements();

	~GraphicsPipelineManager();

private:

	struct Node
	{
		GraphicsPipelineElement* element;
		Node* next;

		~Node();
	};

	Node* head = nullptr;

	int previousTick;
	SdlScreenHandler *sdlScreenHandler;
};