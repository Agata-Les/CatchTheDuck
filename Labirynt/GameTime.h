#pragma once

class GameTime
{
public:
	GameTime();
	~GameTime() = default;

	void update();
	float calculateElapsedTime();
	float getTotalGameTime();
	
private:
	float elapsedTime = 0.0f;
	float totalGameTime = 0.0f;
	float CPUfrequency;
	long long int previousTick;
};
