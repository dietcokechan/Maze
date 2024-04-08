# The Maze Project

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [Related Projects](#related-projects)
- [Licensing](#licensing)
- [Authors](#authors)

## Introduction

Welcome to the 3D Maze Project README! This project explores the exciting world of 3D graphics and gaming by implementing a maze using raycasting techniques. Leveraging the power of OpenGL and C programming, this project combines creativity with technical prowess to provide an immersive and interactive experience. Follow along to dive into the intricacies of raycasting, OpenGL rendering, and maze navigation in a challenging 3D environment. Let's embark on this journey together into the fascinating realm of 3D mazes!

<a href="https://imgur.com/3aM3UNy"><img src="https://i.imgur.com/3aM3UNy.png" title="source: imgur.com" width="500" height="200" /></a>
<a href="https://imgur.com/VrMi7Qr"><img src="https://i.imgur.com/VrMi7Qr.png" title="source: imgur.com" width="500" height="200" /></a>

## Installation

### Clone

Clone repository with running the following command in your terminal:

`git clone https://github.com/dietcokechan/Maze.git`

### Dependencies

After you have cloned the repository, you need install SDL2 on your machine by visiting this [link](https://github.com/libsdl-org/SDL/releases) and downloading the VC version of the latest release.

<a href="https://imgur.com/RpwwQIl"><img src="https://i.imgur.com/RpwwQIl.png" title="source: imgur.com" /></a>

### Compile & Run

After you have installed the dependencies, place the extracted folder inside the root directory of the project. Open a terminal inside the root directory and run the following commands:

1. Build

    `cmake -S . -Bbuild`

2. Make

    `cmake --build build --config Release`

3. Run

    Windows: `start build/Release/Maze.exe base`

    Linux: `./build/Release/Maze.exe base`

Note: `base` is the name of the file containing the map to be rendered inside the game.

## Usage

### Navigation

| KEY | MOVEMENT |
| --- | --- |
| `W` or `UP` Arrow | Move forward |
| `S` or `DOWN` Arrow | Move backward |
| `A` or `LEFT` Arrow | Turn left |
| `S` or `RIGHT` Arrow | Turn right |
| `M` | Toggle map on/off |

## Contributing

- Read the source files in `src` folder and the header files in `inc` folder.
- Clone the repo and make a new branch: <br>
    `$ git checkout https://github.com/dietcokechan/Maze -b [name_of_new_branch].`
- Add a feature, fix a bug, or refactor code.
- Write/update tests for the changes you made, if necessary.
- Update `README.md`, if necessary.
- Open a Pull Request with a comprehensive description of changes.

## Related Projects

[2D Mandelbrot Set Fractal](https://github.com/dietcokechan/2D-Mandelbrot-Set-Fractal) is a computer graphics project developed with SDL2 graphics to render the aforementioned fractal, zooming inside the fractal while taking screenshots, which can then be compiled using `ffmpeg` to create a video.

[Kmyt](https://github.com/dietcokechan/Kmyt-Prototype) is an educational adventure game prototype developed with Unity Game Engine, serving as my university graduation project.

## Licensing

WTFPL

## Authors

Habiba Sameh <@dietcokechan> <habibasamehmosa@gmail.com>
