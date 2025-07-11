#include <iostream>

#include "utils.hpp"

int main()
{
  std::cout << "Program start." << std::endl;

  int startX = 500, startY = 500;
  int endX = getRandomInt(100, 800);
  int endY = getRandomInt(100, 600);

  std::cout << "Program end." << std::endl;
}