# OpenGL Multithreaded Mandelbrot

## Description

This project visualizes the Mandelbrot Set using a multithreaded approach in C++ with OpenGL and GLUT. The application supports zooming and switching color schemes for a dynamic visual experience.

## Features

- Multithreaded computation of the Mandelbrot Set for improved performance.
- Zoom in and out to explore different parts of the Mandelbrot Set.
- Toggle between two color schemes for visual variety.

## Requirements

- C++11 or later
- OpenGL
- GLUT
- GLFW

## Installation

To install the required libraries on macOS using Homebrew, run the following commands:

```sh
brew install glfw
brew install glew
```

## Usage

### Compilation

Use the following command to compile the project:

```sh
clang++ -std=c++11 -o main main.cpp -I/opt/homebrew/include -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw -framework OpenGL -framework GLUT
```

### Running

After compilation, run the program using:

```sh
./main
```

## Controls

- `+` key: Zoom in
- `-` key: Zoom out
- Left mouse button: Toggle between color schemes

## Code Overview

- `main.cpp`: Contains the main logic for computing and displaying the Mandelbrot Set.
- Multithreading is used to compute rows of the Mandelbrot Set in parallel.
- OpenGL and GLUT are used for rendering the computed Mandelbrot Set.
  
<img width="795" alt="Untitled" src="https://github.com/user-attachments/assets/ca514be2-910a-4112-8bab-754d2ceb61e8">
<img width="795" alt="Untitled 2" src="https://github.com/user-attachments/assets/302c441d-06ee-4322-9b88-a9502c85e738">
<img width="795" alt="Untitled 3" src="https://github.com/user-attachments/assets/3501a4ab-a447-48d1-b5f8-96c5d15570ae">
<img width="795" alt="Untitled 4" src="https://github.com/user-attachments/assets/41d2d8a4-b098-428c-83d1-432d015094dc">




## License

This project is licensed under the MIT License. See the LICENSE file for details.

