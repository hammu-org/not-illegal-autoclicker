
# Not Illegal Autoclicker

## Project Description

**Not Illegal Autoclicker** is a cross-platform, open-source tool written in C++ that automates mouse movements and clicks at user-defined intervals. Designed for both Windows and macOS, it provides a modern GUI for configuring click intervals, mouse positions, and a built-in emergency stop timer. The project leverages modern C++ standards, wxWidgets for the GUI, and a cross-platform mouse control library, making it easy to build and extend.

## Features

- **Cross-Platform:** Works on both Windows and macOS.
- **Automated Mouse Actions:** Move the mouse and perform clicks at configurable intervals.
- **Customizable GUI:** Easily adjust click intervals (hours, minutes, seconds, ms), mouse positions (original and target), and random offset.
- **Emergency Stop:** Built-in timer to automatically stop clicking after a user-defined duration (default: 2 minutes) to prevent runaway loops.
- **Simple Build System:** Uses a Makefile for straightforward compilation on supported platforms.
- **Open Source:** Clean, readable code that encourages contributions and extensions.

## Getting Started

### Prerequisites

- **C++17** or newer compiler (e.g., GCC, Clang, MSVC)
- **Make** build system
- **wxWidgets** (for GUI)
  - **Windows:** [wxWidgets download & build instructions](https://docs.wxwidgets.org/3.2/overview_install.html)
  - **macOS:** Install via Homebrew: `brew install wxwidgets`
- **robot-cpp** library (or similar) for cross-platform mouse control
- **Windows:** [MinGW-w64](https://mingw-w64.org/)
- **macOS:** Xcode Command Line Tools (`xcode-select --install`)

### Installation & Running Locally

1. **Clone the repository:**
   ```sh
   git clone https://github.com/yourusername/not-illegal-autoclicker.git
   cd not-illegal-autoclicker
   ```

2. **Install dependencies:**
   - **wxWidgets:**
     - **macOS:**
       ```sh
       brew install wxwidgets
       export PKG_CONFIG_PATH="/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH"
       ```
     - **Windows:** Download and build from [wxWidgets.org](https://www.wxwidgets.org/downloads/), then set up your environment variables as per their docs.

3. **Build the project:**
   ```sh
   make
   ```
   - The executable will be named `not_illegal_autoclicker` (or `not_illegal_autoclicker.exe` on Windows) in the project root.

4. **Run the autoclicker:**
   ```sh
   # On macOS/Linux:
   ./not_illegal_autoclicker
   # On Windows (from cmd or PowerShell):
   .\not_illegal_autoclicker.exe
   ```

**Build Notes:**
- The Makefile will automatically detect your platform and use the correct compiler and wxWidgets flags:
  - On macOS, it uses `clang++` and `wx-config` for flags.
  - On Windows, it uses `g++` and expects you to set `WXWIN` to your wxWidgets install path.
- If you see errors about missing wxWidgets headers or libraries, ensure wxWidgets is installed and your environment variables are set correctly.

## Usage

1. **Configure your click interval and emergency stop:**
   - Set the click interval (hours, minutes, seconds, ms) in the GUI.
   - Set the emergency stop duration (hours, minutes, seconds, ms). The autoclicker will stop after this time (default: 2 minutes).
2. **Set mouse positions:**
   - Enter the original and target X/Y coordinates.
   - Optionally adjust the random offset for more human-like clicking.
3. **Start/Stop:**
   - Press the F12 hotkey to start or stop clicking.
   - The status label will show the current state. If the emergency stop triggers, it will display "Click Status: Emergency Stop".

**Safety Note:**
If the autoclicker moves/clicks outside the app and you lose focus, the emergency stop will prevent it from running forever. You can also set a short stop duration for testing.

**Troubleshooting:**
- If the GUI does not launch or you see errors about wxWidgets, double-check your wxWidgets installation and environment variables.
- On Windows, ensure you are using a terminal with the correct environment (e.g., MSYS2, MinGW-w64, or a properly configured Command Prompt).

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
