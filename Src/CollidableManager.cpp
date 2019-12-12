#include "CollidableManager.hpp"

#include <cstdio>


CollidableManager::CollidableManager(PE_Frog* frog)
	: frog(frog)
{
}

// TODO: study how the elements are inserted given their priority
// TIP: study forward linked list, insert sort
void CollidableManager::AddCollidable(CollidablePipelineElement* element)
{
	if (this->head == nullptr)
	{
		// If there is 0 elements registered, this one shall become head
		this->head = new Node();
		this->head->element = element;
		this->head->next = nullptr;
	}
	if (this->head->element->GetPriority() > element->GetPriority())
	{
		// If head has higher priority than newly registered element
		// then it shall replace it as a head
		auto tmp = this->head;
		this->head = new Node();
		this->head->element = element;
		this->head->next = tmp;
	}
	else
	{
		Node* curr = this->head;

		while (
			curr->next &&
			curr->next->element->GetPriority() <= element->GetPriority()
		)
		{
			curr = curr->next;
		}

		auto tmp = curr->next;
		curr->next = new Node();
		curr->next->element = element;
		curr->next->next = tmp;
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

		auto isOnTheSameXAxis = (x <= rightBorderX && x >= leftBorderX);
		auto isOnTheSameYAxis = (y <= bottomY && y >= upperY);

		if (isOnTheSameYAxis && isOnTheSameXAxis)
		{
			curr->element->Collide(true);

			// stop the collision checking after occuring first
			return;
		}
		else
		{
			curr->element->Collide(false);
		}

		curr = curr->next;
	}
}