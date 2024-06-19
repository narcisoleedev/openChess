# OpenChess 

It's a chess board made in OpenGL on C++ using GLFW and GLAD.
The purpose of this project was to actually learn OpenGL and as an avaliation method for my Computer Graphics class.

### Libraries:

- GLFW
- GLAD 3.3
- GLM
- Assimp
- stb_image.h (already installed)

### To do:

#### Camera:
    - Init Model, View, Projection (DONE)
    - Move left, right, up and down (DONE)
    - Zoom in and out (DONE)

#### Lighting:
    - Ambient Lighting (DONE)
    - Diffuse Light (DONE)
    - Specular Light (DONE)

#### Model:
    - Create model class (DONE)
    - Import chess model (DONE)

#### Wrapping up:
    - Organize makefile (DONE)
    - Organize and comment code (DONE)
    - Create cmake file (DONE)
    - Finish README (DONE)

## How to run:
Firstly, since I am using Linux (more specifically Arch btw), you'll need to install some dependencies.

```
sudo pacman -S glfw assimp mesa mesa-demos cmake 
```

or (for Debian distros)

```
sudo apt-get install libglfw3 libglfw3-dev libassimp-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev cmake
```

In case any dependency is missing, feel free to install it.

After that, download and install GLAD, GLFW, GLM and assimp, and make sure to include standard library headers in the system directories (I installed it using AUR packages).

Then after installing these dependencies you can just do that in the system root folder:

```
cmake .
make 
./openChess
```

In case cmake won't run you can use the oldest Makefile that is inside old/. Just place it in the root folder and make.

Then it'll run! Hope you have an easy time setting this up.