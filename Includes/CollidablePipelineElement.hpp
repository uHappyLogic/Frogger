#pragma once

#include "PipelineElement.h"

class CollidablePipelineElement : public PipelineElement
{
public:

	struct CollisionRect
	{
		int x;
		int y;
		int width;
		int height;
	};

	virtual CollisionRect GetCollisionRect() = 0;

	virtual void Collide(bool collide) = 0;

	virtual int GetPriority() = 0;
};