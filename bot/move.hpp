#pragma once
#include "mouse.hpp"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Accepts a stopFlag pointer; if stopFlag && *stopFlag==false, movement aborts
#include <atomic>
void moveMouseSmooth(int startX, int startY, int endX, int endY, std::atomic<bool> *stopFlag = nullptr);
void moveMouseSmoothReturn(int startX, int startY, int endX, int endY, std::atomic<bool> *stopFlag = nullptr);