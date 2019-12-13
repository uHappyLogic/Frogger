#pragma once

#include "SdlUtils.hpp"
#include "PipelineElement.h"
#include "SdlScreenHandler.h"
#include "CollidableManager.hpp"

class PipelineElementManager
{
public:

	PipelineElementManager(
		CollidableManager *collidableManager);

	void AddElement(CollidablePipelineElement* element);

	void AddElement(PipelineElement* element);

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
	CollidableManager *collidableManager;
};