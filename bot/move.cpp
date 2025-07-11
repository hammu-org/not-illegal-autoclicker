#include "move.hpp"

void moveMouseSmooth(int startX, int startY, int endX, int endY)
{
  // Acceptable ranges for human-like movement
  int minSteps = 100, maxSteps = 150;
  int minDuration = 200, maxDuration = 400; // milliseconds

  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::uniform_int_distribution<> stepsDist(minSteps, maxSteps);
  std::uniform_int_distribution<> durationDist(minDuration, maxDuration);

  // --- Add random offset to the final destination ---
  int maxFinalOffset = 10; // e.g., up to ±10 pixels
  std::uniform_int_distribution<> finalOffsetDist(-maxFinalOffset, maxFinalOffset);
  int offsetX = finalOffsetDist(rng);
  int offsetY = finalOffsetDist(rng);
  endX += offsetX;
  endY += offsetY;

  int steps = stepsDist(rng);
  int totalDurationMs = durationDist(rng);

  std::uniform_real_distribution<> wanderChance(0.0, 1.0);
  std::uniform_int_distribution<> wanderOffset(-20, 20);
  std::uniform_int_distribution<> wanderPause(0, 50);

  double dx = (endX - startX) / static_cast<double>(steps);
  double dy = (endY - startY) / static_cast<double>(steps);
  int sleepMs = totalDurationMs / steps;

  int x = startX, y = startY;
  for (int i = 1; i <= steps; ++i)
  {
    x = static_cast<int>(startX + dx * i);
    y = static_cast<int>(startY + dy * i);

    // Random wandering
    if (wanderChance(rng) < 0.25)
    {
      int wx = x + wanderOffset(rng);
      int wy = y + wanderOffset(rng);
      moveMouse(wx, wy);
    }
    if (wanderChance(rng) < 0.10)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(wanderPause(rng)));
    }

    moveMouse(x, y);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
  }
}
