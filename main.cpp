#include <iostream>

int main()
{
    // Image

    int height = 256;
    int width = 256;

    // Render

    std::cout <<"P3\n" << width << " " << height << "\n255\n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto r = double(i) / (width-1);
            auto g = double(j) / (height-1);
            auto b = 0.0;

            int imgr = int(255.999*r);
            int imgg = int(255.999*g);
            int imgb = int(255.999*b);

            std::cout << imgr << " " << imgg << " " << imgb << "\n";

        }
    }
    return 0;
}