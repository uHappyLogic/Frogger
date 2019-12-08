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

	// returns true if collisions check shall be stopped
	virtual bool Collide(bool collide) = 0;
};