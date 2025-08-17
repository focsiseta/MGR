## Most Generic Raytracer
It's basically raytracing in one weekend (https://raytracing.github.io/books/RayTracingInOneWeekend.html), but I added the possibility to render in "Realtime" the CPU-Generated buffer.

## Things to do
Framerate it's not even bad, it's straight up trash so improving that is surelly something to do.
## Requirements
The project requires that you have SDL2 installed on your machine. SDL2 it's usually available from your package manager as something like libsdl2-dev
## How to compile
Just cd into the repository after downloading it and lanuch g++ main.cpp -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2 -o raytracer

