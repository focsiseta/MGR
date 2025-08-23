## Most Generic Raytracer
It's basically raytracing in one weekend (https://raytracing.github.io/books/RayTracingInOneWeekend.html), but I added the possibility to render in "Realtime" the CPU-Generated buffer. Some funtions are a little different from the source material because I wanted to experiment a bit

## Things to do
Framerate it's trash, speeding up with multithreading will come in the future as well as a GPGPU implementation.
In the meantime, I'll continue expanding on this with the other 2 books in the series.
## Requirements
The project requires that you have SDL2 installed on your machine. SDL2 it's usually available from your package manager as something like libsdl2-dev
## How to compile
Download the repo and cd into it, launch g++ main.cpp -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2 -o raytracer

## Defocus blur working as intended

<img width="800" height="800" alt="image1110" src="https://github.com/user-attachments/assets/d62ffca2-0283-43c3-9e11-dd6ba665752c" />




To output the image you just ./raytracer >> image.ppm, if you've compiled with the last the 2 lines of code uncommented in main.cpp, then the last frame shown before closing the SDL2 window is the one that's going to be rendered. For obvious reasons the generated image will be way better than the realtime feed

As of now pressing w while in realtime adds 0.1 to the defocus angle of the camera

## There is still a long way to go
