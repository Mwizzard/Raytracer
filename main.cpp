#include "Utils.h"
#include "surface.h"
#include "hitableList.h"
#include "sphere.h"
#include "Camera.h"
#include "material.h"

int main()
{

    // World
    HitableList world;

    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<metal>(color(0.9, 0.1, 0.2));

    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3( 1.0, 0.0, -1.2), 0.5, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<sphere>(point3( 0.0, 1.0, 0.0), 0.5, material_right));

    // Cam
    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 1080;
    cam.antialiasingSamples = 100;
    cam.max_depth = 50;

    cam.render(world);

    return 0;
}