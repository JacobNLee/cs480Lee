# PA10: PINBALL

## Controls
		A - Left Paddle
		D - Right Paddle
		Space - Shoot the plunger
		F - to use fragment lighting
		V - to use vertex lighting
		P - to use the default passthrough shaders
		X - Resets the ball
		Left and Right arrow keys - rotate the camera
		Up and Down arrow keys - zoom in and out
		Mouse Wheel - zoom in and out
		RMB and movement - rotate the camera

		In game menu is able to adjust many things

## Extra Credit
	Config File - Lets users make their own pinball tables - PLAY AROUND WITH IT
	
	Holding down spacebar increases force of plunger

	Ability to change angle of table with menu

	Having a menu

	Custom Texture

	Replay

	FPS tracker




## Features
The cube can get stuck. Do try to do that. If you do you lose and will have to restart.

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials). 
This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)
 
### Ubuntu/Linux
The following dependencies are required:
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
sudo apt-get install libassimp-dev
sudo apt-get install libmagick++-dev
sudo apt-get install libbullet-dev
```

## Building and Running
Use cmake

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary.

```bash
mkdir build
cd build
cmake ..
make
./Pinball
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Pinball
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```







