### The buttons 

A : Will start and stop the orbit
S : Will start and stop the rotaion 
Left CLick : Will reverse and resume the orbit 
Right Click: Will reverse and resume the rotaion


### Use cmake to make this project

```bash
mkdir build
cd build
cmake ..
make
./PA2 --Help
```
running 
```bash
./PA2 --Help
```
will help

If I did a horrible job with that, run it like this.
```bash
./PA2 --v ../shaders/330.vert --f ../shaders/330.frag
```

The shaders are in the shader folder


# PA1: Spinning Cube

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```



