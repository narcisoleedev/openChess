## OpenChess 

It's a chess game made in OpenGL/C++ using GLFW and GLAD.

### To do:

#### Camera:
    - Init Model, View, Projection (DONE)
    - Move left, right, up and down (DONE)
    - Zoom in and out (DONE)
    - Rotate with mouse (DONE)

#### Lighting:
    - Ambient Lighting (DONE)
    - Diffuse Light (DONE)
    - Specular Light (DONE)

#### Model:
    - Create model class (TO DO)
    - Import chess model (DONE)

#### Wrapping up:
    - Organize makefile (DONE)
    - Organize and comment code (DONE)
    - Create cmake file (DONE)
    - Finish readme (DONE)

## How to run:
Firstly, since I am using Linux (more specifically Arch btw), you'll need to install some dependencies.

```
sudo pacman -S glfw assimp mesa mesa-demos cmake 
```

or (for Debian distros)

```
sudo apt-get install libglfw3 libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev libassimp-dev cmake
```

In case any dependency is missing, feel free to run.

After that download and install GLAD, GLFW, ASSIMP and make sure to include standard library headers in the system directories (I used AUR packages).

Then after installing these dependencies you can just do that in the system root folder:

```
cmake .
make 
./openChess
```

Then it'll run! Hope you have an easy time setting this up.