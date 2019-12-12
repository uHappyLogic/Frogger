#include "CollidablePipelineElement.hpp"
#include "PipelineElements/PE_TimeProvider.hpp"
#include "PipelineElements/PE_EventHandler.hpp"
#include "PipelineElements/PE_Frog.hpp"


class PE_River : public CollidablePipelineElement
{
public:

	PE_River(
		SDL_Surface* pictureSrc,
		int speed,
		SDL_Surface * screen,
		int screenWidth,
		int screenHeigh,
		PE_TimeProvider* timeProvider,
		bool movingRight,
		PE_Frog* frog,
		int priority
		);

	void Setup() override;

	void Execute() override;

	void Clean() override;

	CollisionRect GetCollisionRect() override;

	void Collide(bool collide) override;

	int GetPriority() override;

private:
	bool movingRight;
	int speed;
	SDL_Surface * screen;
	SDL_Surface * pictureSrc;
	float screenWidth;
	float screenHeigh;
	PE_TimeProvider* timeProvider;
	float distance = 0;
	float currentPosX;
	float currentPosY;
	PE_Frog* frog;
	int priority;
};