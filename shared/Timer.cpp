/*
    Plugin-SDK (Grand Theft Auto) SHARED source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "plugin.h"
#include "Timer.h"

using namespace plugin;

bool Timer::timerInit = false;
std::chrono::time_point<std::chrono::steady_clock> Timer::startTime;

Timer::Timer() {
    if (!timerInit) {
        startTime = std::chrono::steady_clock::now();
        timerInit = true;
    }
}

Timer::~Timer() {

}

float Timer::GetTimeInMilliseconds() {
    return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count());
}

float Timer::GetTimeInSeconds() {
    return GetTimeInMilliseconds() / 1000.0f;
}
