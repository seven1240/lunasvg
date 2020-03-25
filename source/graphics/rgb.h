#ifndef RGB_H
#define RGB_H

namespace lunasvg
{

class Rgb
{
public:
    Rgb();
    Rgb(unsigned int value);
    Rgb(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);

    bool operator==(const Rgb& rgb) const;
    bool operator!=(const Rgb& rgb) const;
    unsigned int value() const;

public:
   unsigned char r;
   unsigned char g;
   unsigned char b;
   unsigned char a;
};

} //namespace lunasvg

#endif // RGB_H
