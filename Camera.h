//
// Created by mwizzard on 5/3/25.
//

#ifndef CAMERA_H
#define CAMERA_H
#include "surface.h"
#include <cassert>

class Camera {
    private:
          int image_height;   // Rendered image height
          double pixel_samples_scale;  // Color scale factor for a sum of pixel samples
          point3 center;         // Camera center
          point3 pixel00_loc;    // Location of pixel 0, 0
          Vector3D pixel_delta_u;  // Offset to pixel to the right
          Vector3D pixel_delta_v;  // Offset to pixel below

          void initialize() {
              pixel_samples_scale = 1.0 / antialiasingSamples;
              // Calculate the image height, and ensure that it's at least 1.
              image_height = int(image_width / aspect_ratio);
              assert(image_width > 0 && image_height > 0);

              auto viewport_height = 2.0;
              auto viewport_width = viewport_height * (double(image_width)/image_height);
              auto focal_length = 1.0;
              center = point3(0, 0, 0);

              //Compute the vectors and delta vectors across the screen
              auto viewport_u = Vector3D(viewport_width, 0, 0);
              auto viewport_v = Vector3D(0, -viewport_height, 0);

              pixel_delta_u = viewport_u / image_width;
              pixel_delta_v = viewport_v / image_height;

              // Compute the location of the upper left pixel (Start of the rendering)
              auto viewport_upper_left = center
                                       - Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
              pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
          }

          //returns the color of a given ray
          color rayColor(const Ray& r, const hittable& world) {

           hitSurfaceRecord rec;
           if (world.hit(r, Interval(0, infinity), rec)) {
               return 0.5 * (rec.normal + color(1,1,1));
           }
           //For now it uses a linear interpolation to create a blend
           Vector3D unit_direction = unit_vector(r.getDirection());
           auto a = 0.5*(unit_direction.getY() + 1.0);
           return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0); // Slight blue hue
          }

      public:
            double aspect_ratio = 1.0;  // Ratio of image width over height
            int image_width  = 100;  // Rendered image width in pixel count
            int antialiasingSamples = 10;
            void render(const hittable& world) {

                initialize();

                std::cout <<"P3\n" << image_width << " " << image_height << "\n255\n";
                for (int j = 0; j < image_height; j++)
                {
                    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                    for (int i = 0; i < image_width; i++)
                    {
                        color pixel_color(0,0,0);
                        for (int sample = 0; sample < antialiasingSamples; sample++) {
                            Ray r = get_ray(i, j);
                            pixel_color += rayColor(r, world);
                        }
                        writeColor(std::cout, pixel_samples_scale * pixel_color);

                    }
                }
                std::clog << "\nDone\n";
            }

            Ray get_ray(int i, int j) const {
                // Construct a camera ray originating from the origin and directed at randomly sampled
                // point around the pixel location i, j.

                auto offset = sample_square();
                auto pixel_sample = pixel00_loc
                                  + ((i + offset.getX()) * pixel_delta_u)
                                  + ((j + offset.getY()) * pixel_delta_v);

                auto ray_origin = center;
                auto ray_direction = pixel_sample - ray_origin;

                return Ray(ray_origin, ray_direction);
            }

            Vector3D sample_square() const {
                return Vector3D(randomDouble() - 0.5, randomDouble() - 0.5, 0);
            }

};
#endif //CAMERA_H
