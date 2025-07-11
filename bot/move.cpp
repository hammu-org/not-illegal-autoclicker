#include "move.hpp"
#include "utils.hpp"

void moveMouseSmooth(int startX, int startY, int endX, int endY, std::atomic<bool> *stopFlag)
{
  // Acceptable ranges for human-like movement
  int minSteps = 50, maxSteps = 80;
  int minDuration = 100, maxDuration = 400; // milliseconds

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
  std::uniform_int_distribution<> wanderOffset(-1, 2);
  std::uniform_int_distribution<> wanderPause(5, 30);

  // double dx = (endX - startX) / static_cast<double>(steps);
  // double dy = (endY - startY) / static_cast<double>(steps);
  double progress = 0.0;
  double eased = 0.0; // ease-in-out curve

  int sleepMs = totalDurationMs / steps;

  int x = startX, y = startY;
  for (int i = 1; i <= steps; ++i)
  {
    if (stopFlag && !(*stopFlag))
      break;
    progress = i / static_cast<double>(steps);
    eased = (1 - cos(progress * M_PI)) / 2; // ease-in-out curve
    x = static_cast<int>(startX + (endX - startX) * eased);
    y = static_cast<int>(startY + (endY - startY) * eased);

    //  x = static_cast<int>(startX + dx * i);
    // y = static_cast<int>(startY + dy * i);

    // Random wandering
    if (wanderChance(rng) < 0.05)
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

void moveMouseSmoothReturn(int startX, int startY, int endX, int endY, std::atomic<bool> *stopFlag)
{
  // Acceptable ranges for human-like movement
  int minSteps = 50, maxSteps = 80;
  int minDuration = 100, maxDuration = 400; // milliseconds

  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::uniform_int_distribution<> stepsDist(minSteps, maxSteps);
  std::uniform_int_distribution<> durationDist(minDuration, maxDuration);

  // --- Add random offset to the final destination ---
  int maxFinalOffset = 10; // e.g., up to ±10 pixels
  std::uniform_int_distribution<> finalOffsetDist(-maxFinalOffset, maxFinalOffset);
  int offsetX = finalOffsetDist(rng);
  int offsetY = finalOffsetDist(rng);
  endX += offsetX * 20;
  endY += offsetY * 30 * (rng() % 2 == 0 ? 1 : -1);
  clampToScreenBleed(endX, endY);

  int steps = stepsDist(rng);
  int totalDurationMs = durationDist(rng);

  std::uniform_real_distribution<> wanderChance(0.0, 1.0);
  std::uniform_int_distribution<> wanderOffset(-2, 2);
  std::uniform_int_distribution<> wanderPause(5, 30);

  // double dx = (endX - startX) / static_cast<double>(steps);
  // double dy = (endY - startY) / static_cast<double>(steps);
  double progress = 0.0;
  double eased = 0.0; // ease-in-out curve

  int sleepMs = totalDurationMs / steps;

  int x = startX, y = startY;
  for (int i = 1; i <= steps; ++i)
  {
    if (stopFlag && !(*stopFlag))
      break;
    progress = i / static_cast<double>(steps);
    eased = (1 - cos(progress * M_PI)) / 2; // ease-in-out curve
    x = static_cast<int>(startX + (endX - startX) * eased);
    y = static_cast<int>(startY + (endY - startY) * eased);

    //  x = static_cast<int>(startX + dx * i);
    // y = static_cast<int>(startY + dy * i);

    // Random wandering
    if (wanderChance(rng) < 0.05)
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
