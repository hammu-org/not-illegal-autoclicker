# Changelog

## [1.0.0] - 2025-07-11

### Major Features
- Modern cross-platform GUI for configuring click intervals, mouse positions, and random offset ([bd9ccef], [ae2eabe], [7537457])
- Emergency stop: user-configurable maximum run duration (hours, minutes, seconds, ms) to prevent runaway loops ([5739ad3])
- Live cursor position display on click events ([7a6ce91])
- F12 hotkey to start/stop autoclicking ([7a6ce91], [1e87208], [0d61e83])
- Human-like smooth mouse movement and random offset for click intervals ([3abeb0c], [9a9c178], [3452893])

### Improvements
- Refined GUI layout and usability ([ae2eabe], [7537457])
- Improved documentation: detailed README with build, usage, and troubleshooting for Windows/macOS ([bd9ccef])
- Enhanced Makefile for wxWidgets integration and platform detection ([d2e554a], [6688160])
- Modular, maintainable codebase with clear separation of mouse movement and click logic ([5217c4d], [be5237b], [ce37fbf], [d63c199])

### Bugfixes & Safety
- Waits for mouse to reach target before clicking ([be5237b])
- Removes redundant wait logic for improved responsiveness ([5217c4d])
- Emergency stop always halts autoclicker after set duration ([5739ad3])

### Other
- Roadmap and project planning updates ([997a5d4])
- Initial implementation, utilities, and setup ([849f873], [624680a], [297e960], [8ef1cf3], [390e37e])

---
Full commit history available in the repository.
