#ifndef COLOR_H
#define COLOR_H
#define RGBA(r, g, b, a)	((r) << 24 | (g) << 16 | (b) << 8 | (a))


#include "vec3.h"

#include <iostream>

#include "interval.h"

using color = vec3;


double linear_to_gamma(double linear){
    if (linear > 0.0) return std::sqrt(linear);
    return 0.0;
}
uint32_t toRGB(double r, double g, double b) {
                                 //gamma 2
    auto rB = static_cast<uint8_t>(clamp(sqrt(r), 0.0, 1.0) * 255.99);
    auto gB = static_cast<uint8_t>(clamp(sqrt(g), 0.0, 1.0) * 255.99);
    auto bB = static_cast<uint8_t>(clamp(sqrt(b), 0.0, 1.0) * 255.99);

    return RGBA(rB, gB, bB, 1);
}
uint32_t colorConversion(const color& pixel_color) {
    return toRGB(pixel_color.x(),pixel_color.y(),pixel_color.z());
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    interval i {0.0,0.999};
    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * i.clamp(r));
    int gbyte = int(255.999 * i.clamp(g));
    int bbyte = int(255.999 * i.clamp(b));
    // int rbyte = int(255.999 * r);
    // int gbyte = int(255.999 * g);
    // int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

int outputPPM(const int width, const int height, const color *imageBuffer[]) {
    if (width <= 0 || height <= 0 || imageBuffer == NULL) { return -1;}
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            const color& pixel = imageBuffer[i][j];
            write_color(std::cout, pixel);
        }
    }
    return 0;
}
class SDLBuffer {
public:
    SDLBuffer(int w, int h) {
            if (SDL_Init(SDL_INIT_EVERYTHING))
                exit(1);
        width = w;
        height = h;
            /* Set up main window. */
            window = SDL_CreateWindow(
                "Raytracer",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                width,
                height,
                SDL_WINDOW_SHOWN
            );
            if (window == NULL)
                exit(2);
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
                exit(3);
            texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);


            renderbuffer = std::shared_ptr<uint32_t>(new uint32_t[width * height], std::default_delete<uint32_t[]>());



        }
        void setPixel(int x, int y, color& c) const{
            uint32_t cc = colorConversion(c);
            renderbuffer.get()[y * width - 1 + x] = cc;
        }
        uint32_t getPixel(int x, int y) const {
            return renderbuffer.get()[y * width - 1 + x];
        }
        void update() {
        auto rawDick = renderbuffer.get();
            void * buffer;
            SDL_LockTexture(texture,NULL,&buffer,&pitch );
            uint32_t * pixel = static_cast<uint32_t*>(buffer);
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    pixel[y * width + x] = rawDick[y * width + x];
                }
            }
        SDL_UnlockTexture(texture);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
        }
        ~SDLBuffer() {
            if (renderer != nullptr) {
                SDL_DestroyRenderer(renderer);
            }
            if (window != nullptr) {
                SDL_DestroyWindow(window);
            }
        }
        private:
        SDL_Renderer    *renderer   = nullptr;
        SDL_Window      *window     = nullptr;
        SDL_Texture     *texture    = nullptr;
        int             width;
        int             height;
        int             pitch;
        std::shared_ptr<uint32_t>      renderbuffer;

};
class colorBuffer {
public:
    color **buffer = nullptr;
    int width = 0;
    int height = 0;
    colorBuffer(int w, int h) {
        width = w;
        height = h;
        buffer = new color *[height];
        for (int i = 0; i < height; i++) {
            buffer[i] = new color[width];
        }
    }
    void setPixel(int x, int y, color c) const{
        buffer[y][x] = c;
    }
    void output() const {
        outputPPM(width, height, const_cast<const color **>(buffer));
    }
    ~colorBuffer() {
        for (int i = 0; i < height; i++) {
            delete[] buffer[i];
        }
        delete[] buffer;
    }

};

#endif