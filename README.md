# 2D Particle Physics Simulation

## Summary
A real-time 2D particle physics simulation built using SFML. The program simulates elastic collisions between particles in a confined space, demonstrating principles of conservation of momentum and energy. Users can create particles by clicking in the window, and watch as they interact with each other and the environment.

## Features
- Real-time particle physics simulation
- Elastic collisions between particles
- Boundary collision detection
- Random particle properties (color, size, mass)
- Interactive particle creation via mouse input
- Smooth particle movement and collision resolution

## Requirements
### General
- CMake (version 3.28 or higher)
- C++17 compatible compiler
- Git

### Windows
- MinGW-w64 or Visual Studio 2017/2019/2022
- MSYS2 (if using MinGW)

### macOS
- Xcode Command Line Tools
- Homebrew (recommended for installing dependencies)

## Build Instructions

### Windows (using MinGW)

1. Install required tools:
   ```bash
   # Using MSYS2
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-gcc
   ```

2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/particle-physics-simulation.git
   cd g
   ```

3. Create and enter build directory:
   ```bash
   mkdir build
   cd build
   ```

4. Generate build files:
   ```bash
   cmake .. -G "MinGW Makefiles"
   ```

5. Build the project:
   ```bash
   cmake --build .
   ```

6. Run the simulation:
   ```bash
   bin/main.exe
   ```

### macOS

1. Install required tools:
   ```bash
   # Install Homebrew if not already installed
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   
   # Install required packages
   brew install cmake
   ```

2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/particle-physics-simulation.git
   cd particle-physics-simulation
   ```

3. Create and enter build directory:
   ```bash
   mkdir build
   cd build
   ```

4. Generate build files and build:
   ```bash
   cmake ..
   cmake --build .
   ```

5. Run the simulation:
   ```bash
   bin/main
   ```

## Usage
1. Launch the application
2. Click anywhere in the window to create particles
3. Watch as particles interact with each other and the environment
4. Close the window to exit the simulation

## Troubleshooting

### Windows
- If you get an error about `std::clamp`, make sure you're using a C++17 compatible compiler
- If OpenAL32.dll is missing, verify that the build process completed successfully
- Ensure your MinGW installation is up to date

### macOS
- If CMake fails to find SFML, try clearing your build directory and rebuilding
- If you get linker errors, make sure you have Xcode Command Line Tools installed