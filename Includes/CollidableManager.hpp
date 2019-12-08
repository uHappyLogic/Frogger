#pragma once


#include "CollidablePipelineElement.hpp"
#include "PipelineElements/PE_Frog.hpp"

class CollidableManager
{
public:

	CollidableManager(PE_Frog* frog);

	void AddCollidable(CollidablePipelineElement* element);

	void TriggerCollision();

private:

	PE_Frog* frog;

	struct Node
	{
		CollidablePipelineElement* element;
		Node* next;

		~Node();
	};

	Node* head = nullptr;
};