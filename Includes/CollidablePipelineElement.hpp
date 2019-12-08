#pragma once

#include "PipelineElement.h"

class CollidablePipelineElement : PipelineElement
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

	virtual void OnCollision() = 0;
};