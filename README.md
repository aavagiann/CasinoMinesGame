# Casino Mines Game

A desktop GUI application built with C++ and the Qt framework that simulates the popular "Mines" casino game. Players can place bets, uncover stars to increase their multiplier, and cash out before hitting a bomb.

## Gameplay Features
* Interactive Grid: A 5x5 grid (25 boxes) where players search for hidden stars while avoiding bombs.
* Dynamic Betting System: Place custom bet amounts with quick options for 1/2x and 2x adjustments.
* Adjustable Difficulty: Choose between 3 to 24 bombs per round, which directly impacts the risk and the reward multipliers.
* Real-time Statistics: Tracks current balance, live game time, and calculates the exact next multiplier coefficient based on the remaining safe boxes.
* Visual Feedback: Custom color palettes and icons for unclicked, opened, and bomb boxes.

## Technologies Used
* Language: C++ (Standard: C++17)
* Framework: Qt (Core, GUI, Widgets)
* Components: Custom Signals & Slots, QGridLayout, QTimer, QMessageBox, and random number generation (std::mt19937).

## Getting Started

### Prerequisites
* Qt Creator with a compatible C++17 compiler (e.g., MinGW or MSVC).
* Qt Version: 5.x or 6.x (The project is configured to disable deprecated APIs before Qt 6.0).

### Build & Run
1. Clone the repository:
   ```bash
   git clone [https://github.com/aavagiann/CasinoMinesGame.git](https://github.com/aavagiann/CasinoMinesGame.git)
