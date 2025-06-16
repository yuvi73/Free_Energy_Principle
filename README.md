# Free Energy Principle Simulation

This project implements a simulation of the Free Energy Principle (FEP) using C++ and Qt. The simulation demonstrates how an agent can minimize its free energy through interaction with an environment.

## Features

- Agent that follows the Free Energy Principle
- Environment with goal-directed dynamics
- Real-time visualization using Qt
- Adjustable parameters for learning rates, noise, and goal attraction
- Interactive GUI with start, pause, and reset controls

## Requirements

- C++17 or later
- CMake 3.10 or later
- Qt5 (Widgets and Charts modules)

## Building the Project

1. Install dependencies:
   ```bash
   # macOS
   brew install qt@5 cmake
   ```

2. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. Run the simulation:
   ```bash
   ./fep_simulation
   ```

## Usage

The GUI provides:
- Real-time plots of agent state, environment state, goal state, and free energy
- Start, pause, and reset controls
- Visual feedback of the agent's learning process

## Parameters

Key parameters can be adjusted in `main.cpp`:
- State dimension
- Sensory dimension
- Learning rates
- Environment noise
- Goal attraction strength

## License

This project is open source and available under the MIT License. 