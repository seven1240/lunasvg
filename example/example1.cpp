#include <vector>
#include "../include/svgdocument.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace lunasvg;

int main()
{
    SVGDocument document;
    if(!document.loadFromFile("tiger.svg"))
        return -1;

    int width;
    int height;
    document.dimensions(width, height);
    if(height < 1)
        height = 540;
    if(width < 1)
        width = 540;

    std::vector<unsigned char> pixels(height*width*4);
    Bitmap bitmap;
    bitmap.pixels = &pixels[0];
    bitmap.width = width;
    bitmap.height = height;
    document.render(bitmap);
    stbi_write_png("tiger.svg.png", bitmap.width, bitmap.height, 4, bitmap.pixels, 0);

    return 0;
}
