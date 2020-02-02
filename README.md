## Ess3D

#### About

Ess3D is a general purpose game engine written in C++. The rendering is done with OpenGL 3. 

The project initially started as a 2D game from which I've broken out a 2D engine that I'm now trying to refactor and develop into having 3D capabilities. The engine's main focus is efficient 3D rendering, GUI rendering, audio management, resource management and interpolated physics simulation (using a 3rd party lib).

I currently have no intention - and probably never will - of building an editor for this game engine, it's simply a C++ library that can be used in your project.

#### Current State

Currently in very early stages, trying to refactor the old code and come up with a better design, separating the 2D part and developing the new 3D features.

#### How to build

All the dependencies have been included on VCS. You can use CLion directly to build and run (with VS compiler) or generate a VS solution with CMake. 