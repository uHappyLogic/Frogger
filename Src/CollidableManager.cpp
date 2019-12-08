#include "CollidableManager.hpp"

#include <cstdio>


CollidableManager::CollidableManager(PE_Frog* frog)
	: frog(frog)
{
}

void CollidableManager::AddCollidable(CollidablePipelineElement* element)
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

void CollidableManager::TriggerCollision()
{
	Node* curr = this->head;

	float x = frog->GetCenterX();
	float y = frog->GetCenterY();

	while (curr)
	{
		auto rect = curr->element->GetCollisionRect();

		float leftBorderX = rect.x - rect.width / 2;
		float rightBorderX = rect.x + rect.width / 2;

		float upperY = (rect.y - rect.height / 2);
		float bottomY = (rect.y + rect.height / 2);

		/*
		printf("X [%4.2f; %4.2f] Y[%4.2f; %4.2f]",
			leftBorderX, rightBorderX, bottomY, upperY
		);
		*/

		auto isOnTheSameXAxis = (x <= rightBorderX && x >= leftBorderX);
		auto isOnTheSameYAxis = (y <= bottomY && y >= upperY);

		if (isOnTheSameYAxis && isOnTheSameXAxis)
		{
			if (curr->element->Collide(true))
				return;
		}
		else
		{
			curr->element->Collide(false);
		}

		curr = curr->next;
	}
}