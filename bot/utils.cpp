#include "utils.hpp"

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <ApplicationServices/ApplicationServices.h>
#endif

Point getCurrentMousePos()
{
#ifdef _WIN32
    POINT p;
    if (GetCursorPos(&p))
    {
        return {static_cast<int>(p.x), static_cast<int>(p.y)};
    }
    else
    {
        return {0, 0};
    }

#elif defined(__APPLE__)
    CGEventRef event = CGEventCreate(NULL);
    CGPoint loc = CGEventGetLocation(event);
    CFRelease(event);
    return {static_cast<int>(loc.x), static_cast<int>(loc.y)};
#else
    return {0, 0};
#endif
}

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int getRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

double getRandomDouble(double min, double max)
{
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

void sleepRandom(int minMs, int maxMs)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(minMs, maxMs)));
}

int randomOffset(int base, int range)
{
    std::uniform_int_distribution<int> dist(-range, range);
    return base + dist(rng);
}