//
// Created by focsiseta on 8/9/25.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "color.h"
#include "material.h"
#include "objects.h"
#include "vec3.h"

#include <SDL2/SDL.h>

class camera {
public:
    vec3 cameraPosition; //cameraCenter
    vec3 viewDirection;
    double yaw = 0.0;
    int raySamples = 25;
    camera(vec3 center,int width,int height,double fLength,double viewPortH) {
        aspectRatio = double(width)/ double(height);
        cameraPosition = center;
        imageWidth = width;
        imageHeight = imageWidth / aspectRatio;
        imageHeight = imageHeight <= 0 ? 1 : imageHeight;
        std::clog <<"Image resolution: "<< imageWidth << "x" << imageHeight << std::endl;
        focalLength = fLength;
        viewPortHeight = viewPortH;
        viewPortWidth = viewPortHeight * aspectRatio;
        viewPortU = vec3(viewPortWidth,0.0,0.0);
        viewPortV = vec3(0.0,-viewPortHeight,0.0);
        deltaU = viewPortU / imageWidth;
        deltaV = viewPortV / imageHeight;
        viewDirection = cameraPosition - vec3(0,0,focalLength);
        upperLeftCorner = viewDirection - viewPortU*0.5 - viewPortV*0.5;
        pixel00Loc  =  upperLeftCorner + 0.5*vec3(deltaU + deltaV);
    }


    color rayColor(ray& r, hittable& hittable, int bounces) {
        if (bounces <= 0.0) return color{0,0,0};
        hitRecord rec;
        interval delta{0.001,infinity};
        if (hittable.hit(r,delta,rec)) {
            //auto normal = 0.5*(rec.normal+vec3(1,1,1));
            //matte material
            shared_ptr<material> mat = rec.mat;
            color attenuation{};
            ray scatteredRay{};
            bool hasScattered =  mat->scatter(r,rec,attenuation,scatteredRay);
            if (hasScattered) {
                return attenuation * rayColor(scatteredRay,hittable,bounces -1);
            }
            return vec3(0,0,0);
            // vec3 newDiretion = vectorInsideEmisphere(rec.normal); //simple ray scattering (rejection method)
            // //vec3 point = rec.normal +unit_vector(random_vector(-1,1));
            // ray bounce{rec.hitPosition,newDiretion};
            //
            // return attenuation;

        }
        auto tt = (unit_vector(r.direction).y() + 1.0) * 0.5;
        color c1 = color{0.5, 0.7, 1.0};
        color c2 = color{1.0,1.0,1.0};
        //return c1 * tt + (1 - tt) * c2;
        return color{1,1,1};
    }
    colorBuffer render(hittable& world) {
        colorBuffer result(imageWidth, imageHeight);
        for (int i = 0; i < imageHeight; i++) {
            for (int j = 0; j < imageWidth; j++) {
                vec3 pixelLocation = pixel00Loc + deltaU*double(j) + deltaV * double(i);
                vec3 direction = pixelLocation - cameraPosition;
                double tt = (unit_vector(direction).y() + 1.0) * 0.5;
                // color c1 = color{0.5, 0.7, 1.0};
                // color c2 = color{1.0,1.0,1.0};
                ray r{cameraPosition,direction};
                color main = supersampling(i,j,world);
                //color c = tt * c1 + (1 - tt) * c2;
                result.setPixel(j,i,main);


            }
        }
        return result;
    }
    color realTimeRayColor(ray& r, hittable& world,int bounces) {
        if (bounces <= 0.0) return color{0,0,0};
        hitRecord rec;
        interval delta{0.001,infinity};
        if (world.hit(r,delta,rec)) {
            ray nextRay{};
            color c{};
            if (rec.mat->scatter(r,rec,c,nextRay)) {
                return c * realTimeRayColor(nextRay,world,bounces - 1);
            }
        }
        //background ray color
        return vec3{1,1,1};

    }
    void renderSDL(hittable& world) {
        SDL_Event   ev;
        SDLBuffer result(imageWidth, imageHeight);
        bool keepRunning = true;
        //colorBuffer result(imageWidth, imageHeight);
        while (keepRunning){
            while (SDL_PollEvent(&ev) != 0) {
                if (ev.type == SDL_QUIT)
                    keepRunning = false;
                if (ev.key.keysym.sym == SDLK_s) {
                    cameraPosition += vec3(0,0,0.1);
                    viewDirection = cameraPosition - vec3(0,0,focalLength);
                    //std::clog << cameraPosition << std::endl;
                    upperLeftCorner = viewDirection - viewPortU*0.5 - viewPortV*0.5;
                    pixel00Loc  =  upperLeftCorner + 0.5*vec3(deltaU + deltaV);

                }
                if (ev.key.keysym.sym == SDLK_d) {
                    yaw -= 0.09;
                    viewDirection = vec3(viewDirection.x() * cos(yaw) + viewDirection.z() * sin(yaw),viewDirection.y(),viewDirection.x() * -sin(yaw) + viewDirection.z() * cos(yaw));
                    upperLeftCorner =  viewDirection - viewPortU*0.5 - viewPortV*0.5;
                    pixel00Loc  =  upperLeftCorner + 0.5*vec3(deltaU + deltaV);
                }
            }
            for (int i = 0; i < imageHeight; i++) {
                for (int j = 0; j < imageWidth; j++) {
                    vec3 pixelLocation = pixel00Loc + deltaU*double(j) + deltaV * double(i);
                    vec3 direction = pixelLocation - cameraPosition;
                    double tt = (unit_vector(direction).y() + 1.0) * 0.5;
                    // color c1 = color{0.5, 0.7, 1.0};
                    // color c2 = color{1.0,1.0,1.0};
                    ray r{cameraPosition,direction};
                    interval delta{0.001,infinity};
                    hitRecord rec;
                    color c = realTimeRayColor(r,world,2);



                    //color main = supersampling(i,j,world);
                    //color c = tt * c1 + (1 - tt) * c2;
                    //color c = rayColor(r,world,1);
                    result.setPixel(j,i,c);


                }
            }
            result.update();
        }

    }
    ray rayAround(int i, int j) const {
        vec3 square = sample_square();
        //vec3 randomSubPixel = pixel00Loc + square + deltaU * (double(j) + 0.5) + deltaV * (double(i) + 0.5);
        vec3 randomSubPixel = pixel00Loc + (j + square.x()) * deltaU + (i + square.y()) * deltaV;
        vec3 direction = randomSubPixel - cameraPosition;
        ray r{cameraPosition,direction};
        return r;
    }
    color supersampling(int i, int j,hittable& world) {
        color c{};
        for (int s = 0; s < raySamples; s++) {
            ray r = rayAround(i,j);
            c += realTimeRayColor(r,world,25);
        }
        //linear averege
        return c/raySamples;
    }
    int getImageWidth() const {return imageWidth;};
    int getImageHeight() const {return imageHeight;};
private:
    int imageWidth, imageHeight;
    double aspectRatio;
    double focalLength;
    double viewPortHeight;
    double viewPortWidth;
    vec3 viewPortU;
    vec3 viewPortV;
    vec3 deltaU;
    vec3 deltaV;
    vec3 upperLeftCorner;
    vec3 pixel00Loc;


};

#endif //CAMERA_H
