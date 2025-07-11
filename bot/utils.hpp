#pragma once
#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <algorithm>

struct Point
{
    int x;
    int y;

    bool isValid() const { return x >= 0 && y >= 0; }
};
struct ScreenRect
{
    int left;
    int top;
    int right;
    int bottom;
};

Point getCurrentMousePos();
ScreenRect getScreenBounds();
void clampToScreen(int &x, int &y);
void clampToScreenBleed(int &x, int &y);

int getRandomInt(int min, int max);
double getRandomDouble(double min, double max);
void sleepRandom(int minMs, int maxMs);
int randomOffset(int base, int range);
