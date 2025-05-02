#include <iostream>
#include "Color.h"
#include "Vector3D.h"

int main()
{
    // Image

    int height = 256;
    int width = 256;

    // Render

    std::cout <<"P3\n" << width << " " << height << "\n255\n";
    for (int j = 0; j < height; j++)
    {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; i++)
        {
            auto pixel_color = color(double(i)/(width-1), double(j)/(height-1), 0);
            writeColor(std::cout, pixel_color);
        }
    }
    std::clog << "\nDone\n";
    return 0;
}