#include "PipelineElementManager.h"


PipelineElementManager::PipelineElementManager(CollidableManager *collidableManager)
	: collidableManager(collidableManager)
{

}

void PipelineElementManager::AddPipeline(CollidablePipelineElement* element)
{
	collidableManager->AddCollidable(element);
	this->AddPipeline((PipelineElement*)element);
}

void PipelineElementManager::AddPipeline(PipelineElement* element)
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


void PipelineElementManager::RunAllElements()
{
	Node* curr = this->head;

	while (curr)
	{
		curr->element->Execute();
		curr = curr->next;
	}
}


void PipelineElementManager::Init()
{
	Node* curr = this->head;

	while (curr)
	{
		curr->element->Setup();
		curr = curr->next;
	}
}

PipelineElementManager::~PipelineElementManager()
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

PipelineElementManager::Node::~Node()
{
	delete element;
	element = nullptr;
}