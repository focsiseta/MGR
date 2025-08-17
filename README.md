## Most Generic Raytracer
It's basically raytracing in one weekend (https://raytracing.github.io/books/RayTracingInOneWeekend.html), but I added the possibility to render in "Realtime" the CPU-Generated buffer.

## Things to do
Framerate it's not even bad, it's straight up trash so improving that is surelly something to do.
## Requirements
The project requires that you have SDL2 installed on your machine. SDL2 it's usually available from your package manager as something like libsdl2-dev
## How to compile
Download the repo and cd into it, launch g++ main.cpp -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2 -o raytracer

![image](https://github.com/user-attachments/assets/ee0789ac-ef00-480f-b74e-7fa80691b248)

To output the image you just ./raytracer >> image.ppm, and if you've compiled with the last the lines of code uncommented in main.cpp, then the last frame is the one that's going to be rendered. For obvious reasons the generated image will be way better than the realtime feed

## There is still a long way to go
