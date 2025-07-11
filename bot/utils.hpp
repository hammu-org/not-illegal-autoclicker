#pragma once
#include <chrono>
#include <random>
#include <thread>
#include <iostream>

struct Point
{
    int x;
    int y;

    bool isValid() const { return x >= 0 && y >= 0; }
};

Point getCurrentMousePos();

int getRandomInt(int min, int max);
double getRandomDouble(double min, double max);
void sleepRandom(int minMs, int maxMs);
int randomOffset(int base, int range);
