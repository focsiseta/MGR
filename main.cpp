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
    auto material_ground = make_shared<lambert>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambert>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<metallic>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<metallic>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-0.5,    0.0, -1.5),   0.5, material_left));

    //world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));
    //
    // shared_ptr<lambert> lambertMat = make_shared<lambert>(color{0.0,0.7,0.0});
    // shared_ptr<metallic> metallicMat = make_shared<metallic>(color{0.5,0.5,0.5});
    // shared_ptr<metallic> metallicMat1 = make_shared<metallic>(color{1.0,0.5,0.6});
    // metallicMat1->setFuzzy(0.2);
    // shared_ptr<lambert> lambertTerrain = make_shared<lambert>(color{0.0,0.2,0.5});
    // shared_ptr<dielectric> dielectricMat = make_shared<dielectric>(color{1,1,1},INDEX_AIR);
    //
    // //terra
    // //list.add(make_shared<sphere>(vec3{1.0,    0.0, -75.0},50.0,lambertMat));
    // list.add(make_shared<sphere>(vec3{0.0,-100.5,-1.0},100.0,lambertTerrain));
    // // //sfera
    // // list.add(make_shared<sphere>(vec3{2,    0.0, -5},0.5,metallicMat));
    //
    // //
    // list.add(make_shared<sphere>(vec3{0,    0.0, -3.0},0.5,dielectricMat));
    // list.add(make_shared<sphere>(vec3{0,    0.0, -5},0.5,lambertMat));
    //
    // // list.add(make_shared<sphere>(vec3{0.0,    0.0, -2.3},0.5,metallicMat1));
    camera dolly{vec3{0,0,0},IMG_WIDTH,IMG_HEIGHT,2,2};
    dolly.renderSDL(world);
    auto frame = dolly.render(world);
    frame.output();


}