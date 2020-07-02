#pragma once
#include "SDL.h"
#include <iostream>
class Timer
{
private:
	const int FRAMES_PER_SECOND = 60, SECOND=1000;
	const double MILLISECS_PER_FRAME = 1000 / 60;
	int initialTime, time, deltaTime, FPScounter = 0;

public:
	//constructors
	Timer();

	//functions
	void startTimer();
	void capeFPS();
	int getFPS();

	//destructors
	~Timer();
};

