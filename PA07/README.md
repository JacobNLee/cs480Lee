# PA7: SOLAR SYSTEM
## PA7 Collaborators
Jacob Lee
Cayler Miley
Austin Emery

## Controls
### The buttons
```bash

Left + right arrow will cycle planets
- will slow the sim
+ will speed

c will give a close top view 
v will give a far top view

ESC: Will end the program
```
## Build
### Use cmake to make this project

```bash
mkdir build
cd build
cmake ..
make
```

There is now a config file. Just run it like ./PA7!!!
```bash
./PA7 

```

The shaders are in the shader folder and
all of the assets are in the planets folder (even the moons)

## Dependencies, Building, and Running

### Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev 
sudo apt-get install libassimp-dev
sudo apt-get install libmagick++-dev
```



