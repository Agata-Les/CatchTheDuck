#include "GameTime.h"
#include <Windows.h>

GameTime::GameTime()
{
	LARGE_INTEGER CPUinfo;

	QueryPerformanceFrequency(&CPUinfo);
	CPUfrequency = (float)(CPUinfo.QuadPart);

	QueryPerformanceCounter(&CPUinfo);
	previousTick = CPUinfo.QuadPart;
}

void GameTime::update()
{
	LARGE_INTEGER CPUinfo;
	QueryPerformanceCounter(&CPUinfo);

	previousTick = CPUinfo.QuadPart;
	totalGameTime += elapsedTime;
}

float GameTime::calculateElapsedTime()
{
	LARGE_INTEGER CPUinfo;
	QueryPerformanceCounter(&CPUinfo);

	elapsedTime = (CPUinfo.QuadPart - previousTick) / CPUfrequency;
	
	return elapsedTime;
}

float GameTime::getTotalGameTime()
{
	return totalGameTime;
}
