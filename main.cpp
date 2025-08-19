#include "realtimeRender.h"
#include "camera.h"
#include "utilities.h"
#include "color.h"
#include "objects.h"
#include "ray.h"
#include "settings.h"
#include "vec3.h"
double aspectRatio = IMG_WIDTH / IMG_HEIGHT;

int main() {
    hittableList world{};


    auto material_ground = make_shared<lambert>(color(0.8, 0, 0.8));
    auto material_center = make_shared<lambert>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(color(.9, .9, .9),INDEX_DIAMOND);
    auto material_bubble = make_shared<dielectric>(color(.9, .9, .9),1.0/INDEX_DIAMOND);
    auto material_right  = make_shared<metallic>(color(0.8, 0.8, 0.8));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    camera dolly{IMG_WIDTH,IMG_HEIGHT,vec3{-1,0,3},vec3{0,0,-1},2};
    dolly.renderSDL(world);
    auto frame = dolly.render(world);
    frame.output();


}