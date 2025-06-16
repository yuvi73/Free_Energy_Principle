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

### Local Build

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

### Docker Build

1. Build the Docker image:
   ```bash
   docker build -t fep-simulation .
   ```

2. Run the container:
   ```bash
   docker run -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix fep-simulation
   ```

Note: For Docker on macOS, you'll need to install and configure XQuartz to display the GUI:
1. Install XQuartz: `brew install --cask xquartz`
2. Start XQuartz and enable "Allow connections from network clients" in XQuartz preferences
3. Restart your computer
4. Run the container with:
   ```bash
   xhost +  # Allow X server connections
   docker run -e DISPLAY=host.docker.internal:0 -v /tmp/.X11-unix:/tmp/.X11-unix fep-simulation
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