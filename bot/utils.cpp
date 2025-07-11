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

ScreenRect getScreenBounds()
{
#ifdef _WIN32
    RECT r;
    GetClientRect(GetDesktopWindow(), &r);
    return {r.left, r.top, r.right, r.bottom};

#elif defined(__APPLE__)
    auto mainDisplay = CGMainDisplayID();
    CGRect bounds = CGDisplayBounds(mainDisplay);
    return {
        static_cast<int>(bounds.origin.x),
        static_cast<int>(bounds.origin.y),
        static_cast<int>(bounds.origin.x + bounds.size.width),
        static_cast<int>(bounds.origin.y + bounds.size.height)};

#else
    return {0, 0, 1920, 1080}; // fallback
#endif
}

void clampToScreen(int &x, int &y)
{
    ScreenRect bounds = getScreenBounds();
    x = std::clamp(x, bounds.left + 1, bounds.right - 2);
    y = std::clamp(y, bounds.top + 1, bounds.bottom - 2);
}

void clampToScreenBleed(int &x, int &y)
{
    ScreenRect bounds = getScreenBounds();
    const int bleedMarginX = (bounds.right - bounds.left) / 20; // 5% on each side
    const int bleedMarginY = (bounds.bottom - bounds.top) / 20; // 5% on top/bottom
    x = std::clamp(x, bounds.left + bleedMarginX, bounds.right - bleedMarginX);
    y = std::clamp(y, bounds.top + bleedMarginY, bounds.bottom - bleedMarginY);
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