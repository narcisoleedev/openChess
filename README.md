# OpenChess 

It's a chess board made in OpenGL on C++ using GLFW and GLAD.
The purpose of this project was to actually learn OpenGL and as an avaliation method for my Computer Graphics class.

### Libraries:

- GLFW
- GLAD 3.3
- GLM
- Assimp
- stb_image.h (already installed)

### Depedencies:
```
        linux-vdso.so.1 (0x00007ffc14be6000)
        libGL.so.1 => /usr/lib/libGL.so.1 (0x00007d7f0345a000)
        libX11.so.6 => /usr/lib/libX11.so.6 (0x00007d7f0331c000)
        libXrandr.so.2 => /usr/lib/libXrandr.so.2 (0x00007d7f0330f000)
        libXi.so.6 => /usr/lib/libXi.so.6 (0x00007d7f032fb000)
        libassimp.so.5 => /usr/lib/libassimp.so.5 (0x00007d7f02a00000)
        libstdc++.so.6 => /usr/lib/libstdc++.so.6 (0x00007d7f02600000)
        libm.so.6 => /usr/lib/libm.so.6 (0x00007d7f0320d000)
        libgcc_s.so.1 => /usr/lib/libgcc_s.so.1 (0x00007d7f031e8000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007d7f0241e000)
        libGLdispatch.so.0 => /usr/lib/libGLdispatch.so.0 (0x00007d7f03130000)
        libGLX.so.0 => /usr/lib/libGLX.so.0 (0x00007d7f029ce000)
        libxcb.so.1 => /usr/lib/libxcb.so.1 (0x00007d7f029a3000)
        libXext.so.6 => /usr/lib/libXext.so.6 (0x00007d7f0298e000)
        libXrender.so.1 => /usr/lib/libXrender.so.1 (0x00007d7f03121000)
        libz.so.1 => /usr/lib/libz.so.1 (0x00007d7f02974000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007d7f035d8000)
        libXau.so.6 => /usr/lib/libXau.so.6 (0x00007d7f0311c000)
        libXdmcp.so.6 => /usr/lib/libXdmcp.so.6 (0x00007d7f0296c000)
```

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