#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

class Timer
{

public:
	void StartTimer();
	double GetTime();
	double GetFrameTime();


private:
	double countsPerSecond = 0.0;
	__int64 CounterStart = 0;
	__int64 frameTimeOld = 0;
};

