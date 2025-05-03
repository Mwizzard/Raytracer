#include "Utils.h"
#include "surface.h"
#include "hitableList.h"
#include "sphere.h"
#include "Camera.h"

int main()
{

    // World
    HitableList world;

    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Cam
    Camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.antialiasingSamples = 100;
    cam.max_depth = 50;

    cam.render(world);

    return 0;
}