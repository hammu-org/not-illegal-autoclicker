#include "utils.hpp"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

double getRandomDouble(double min, double max) {
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

void sleepRandom(int minMs, int maxMs) {
    std::this_thread::sleep_for(std::chrono::milliseconds(getRandomInt(minMs, maxMs)));
}
