#pragma once

#include "GraphicsPipelineManager.h"


GraphicsPipelineManager::GraphicsPipelineManager(SdlScreenHandler *sdlScreenHandler)
	: sdlScreenHandler(sdlScreenHandler)
{
	this->previousTick = SDL_GetTicks();
}

void GraphicsPipelineManager::AddPipeline(GraphicsPipelineElement* element)
{
	if (this->head == nullptr)
	{
		// Insert new element as a head
		this->head = new Node();
		this->head->element = element;
		this->head->next = nullptr;
	}
	else
	{
		// Insert new element as a last node
		Node* currentLast = this->head;

		while (currentLast->next)
			currentLast = currentLast->next;

		currentLast->next = new Node();
		currentLast->next->element = element;
		currentLast->next->next = nullptr;
	}
}


void GraphicsPipelineManager::RunAllElements()
{
	int currentTick = SDL_GetTicks();
	float delta = delta = (this->previousTick - currentTick) * 0.001f;

	Node* curr = this->head;

	while (curr)
	{
		curr->element->Draw(*this->sdlScreenHandler->screen, delta);
		curr = curr->next;
	}
}


void GraphicsPipelineManager::Init()
{
	Node* curr = this->head;

	while (curr)
	{
		curr->element->Setup(*this->sdlScreenHandler->screen);
		curr = curr->next;
	}
}

GraphicsPipelineManager::~GraphicsPipelineManager()
{
	Node* prev = this->head;

	if (!prev)
		return;

	Node* curr = nullptr;

	while (prev->next)
	{
		curr = prev->next;
		delete prev;
		prev = curr;
	}

	delete prev;
}

GraphicsPipelineManager::Node::~Node()
{
	delete element;
	element = nullptr;
}