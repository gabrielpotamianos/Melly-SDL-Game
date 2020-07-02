#include "Timer.h"



Timer::Timer()
{
}

void Timer::startTimer()
{
	if (SDL_GetTicks() % SECOND>=0 && SDL_GetTicks() % SECOND<=20)
	{
		std::cout << getFPS() << std::endl;
		FPScounter = 0;
	}
	initialTime = SDL_GetTicks();
}

void Timer::capeFPS()
{
	time = SDL_GetTicks();
	deltaTime = time - initialTime;
	if (deltaTime < MILLISECS_PER_FRAME)
		SDL_Delay(MILLISECS_PER_FRAME - deltaTime);
	else
		std::cout << " EXCEEDS A FRAME TIME!!!!" << std::endl;
	FPScounter++;

}

int Timer::getFPS()
{
	return FPScounter;
}


Timer::~Timer()
{
}
