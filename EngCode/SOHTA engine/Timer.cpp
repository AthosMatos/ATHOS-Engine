#include "Timer.h"

void Timer::StartTimer()
{
    LARGE_INTEGER frequencyCount;
    QueryPerformanceFrequency(&frequencyCount);

    countsPerSecond = double(frequencyCount.QuadPart);

    QueryPerformanceCounter(&frequencyCount);
    CounterStart = frequencyCount.QuadPart;
}

double Timer::GetTime()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

double Timer::GetFrameTime()
{
    LARGE_INTEGER currentTime;
    __int64 tickCount;
    QueryPerformanceCounter(&currentTime);

    tickCount = currentTime.QuadPart - frameTimeOld;
    frameTimeOld = currentTime.QuadPart;

    if (tickCount < 0.0f)
        tickCount = 0.0f;

    return float(tickCount) / countsPerSecond;
}
