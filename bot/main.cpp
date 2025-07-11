#include <iostream>
#include "move.hpp"

int main()
{
  std::cout << "Program start." << std::endl;

  moveMouseSmooth(200, 500, 1500, 200);

  std::cout << "Program end." << std::endl;
}