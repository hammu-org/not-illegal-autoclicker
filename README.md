i# Not Illegal Autoclicker

## Project Description

**Not Illegal Autoclicker** is a cross-platform, open-source tool written in C++ that automates mouse movements and clicks at user-defined intervals. Designed for both Windows and macOS, it aims to provide a simple, customizable, and efficient solution for tasks requiring repetitive mouse actions. The project leverages modern C++ standards and a cross-platform mouse control library, making it easy to build and extend.

## Features

- **Cross-Platform:** Works on both Windows and macOS.
- **Automated Mouse Actions:** Move the mouse and perform clicks at configurable intervals.
- **Customizable:** Easily adjust click intervals, mouse positions, and more.
- **Simple Build System:** Uses a Makefile for straightforward compilation on supported platforms.
- **Open Source:** Clean, readable code that encourages contributions and extensions.

## Getting Started

### Prerequisites

- **C++17** or newer compiler (e.g., GCC, Clang, MSVC)
- **Make** build system
- **robot-cpp** library (or similar) for cross-platform mouse control
- **Windows:** [MinGW-w64](https://mingw-w64.org/)
- **macOS:** Xcode Command Line Tools (`xcode-select --install`)

### Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/not-illegal-autoclicker.git
   cd not-illegal-autoclicker
   ```

2. **Install dependencies:**
   - Follow the instructions for installing `robot-cpp` or your chosen mouse automation library.

3. **Build the project:**
   ```sh
   make
   ```

4. **Run the autoclicker:**
   ```sh
   ./autoclicker
   ```

## Usage

By default, the autoclicker will move the mouse to a specified position and perform a left-click every 2 seconds. You can modify the interval and position in the source code, or extend the project to accept command-line arguments for more flexibility.

**Example main loop:**
```cpp
#include "robot.h"
#include <thread>
#include <chrono>

int main() {
  while (true) {
    Robot::Mouse::MoveSmooth({500, 500});
    Robot::Mouse::Click(Robot::MouseButton::Left);
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
}
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.

## License

This project is licensed under the MIT License.

## Disclaimer

This tool is intended for legal, ethical, and personal productivity purposes only. Please ensure your usage complies with all applicable laws and terms of service. The authors are not responsible for misuse.

## Credits

- Inspired by the open-source community and cross-platform automation tools.
- Built with C++ and the `robot-cpp` library for mouse automation.

## Contact

For questions or suggestions, please open an issue on the repository.
