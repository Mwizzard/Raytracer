#include <iostream>
#include "Color.h"
#include "Vector3D.h"
#include "Ray.h"
#include <cassert>

//Function to determine if a ray hits a sphere
double hit_sphere(const point3& center, double radius, const Ray& r) {
    Vector3D oc = center - r.getOrigin();
    auto a = dotProduct(r.getDirection(), r.getDirection());
    auto b = -2.0 * dotProduct(r.getDirection(), oc);
    auto c = dotProduct(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - std::sqrt(discriminant) ) / (2.0*a);
    }
}
//returns the color of a given ray
color rayColor(const Ray& r) {
    //if the ray hits the sphere, we replace the color with full red
    auto hit = hit_sphere(point3(0,0,-1), 0.5, r);
    if (hit > 0)
    {
        Vector3D N = unit_vector(r.at(hit) - Vector3D(0,0,-1));
        return 0.5*color(N.getX()+1, N.getY()+1, N.getZ()+1);
    }
    //For now it uses a linear interpolation to create a blend
    Vector3D unit_direction = unit_vector(r.getDirection());
    auto a = 0.5*(unit_direction.getY() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); // Slight blue hue
}

int main()
{
    // Viewport height and width
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    assert(image_width > 0 && image_height > 0);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    //Compute the vectors and delta vectors across the screen
    auto viewport_u = Vector3D(viewport_width, 0, 0);
    auto viewport_v = Vector3D(0, -viewport_height, 0);

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Compute the location of the upper left pixel (Start of the rendering)
    auto viewport_upper_left = camera_center
                             - Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // Render

    std::cout <<"P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            color pixel_color = rayColor(r);
            writeColor(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone\n";
    return 0;
}