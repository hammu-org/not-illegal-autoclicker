#pragma once
#include "mouse.hpp"

// Accepts a stopFlag pointer; if stopFlag && *stopFlag==false, movement aborts
#include <atomic>
void moveMouseSmooth(int startX, int startY, int endX, int endY, std::atomic<bool> *stopFlag = nullptr);
