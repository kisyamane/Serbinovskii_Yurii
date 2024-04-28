#pragma once

#include <array>
#include <string>



struct Rectangle
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int thickness;
    std::array<int, 3> color;
    bool fill;
    std::array<int, 3> fill_color;
};

struct Ornament
{
    std::string pattern; //изменить в дальнейшем
    std::array<int, 3> color;
    int thickness;
    int count;
};

struct Rotate
{
    std::array<int, 2> left_up;
    std::array<int, 2> right_down;
    int angle;
};

struct Circle
{
    std::array<int, 2> center;
    int radius;
    int thickness;
    std::array<int, 3> color;
    bool fill;
    std::array<int, 3> fill_color;
    Circle(std::array<int, 2> center, int radius, int thickness, std::array<int, 3> color, bool fill, std::array<int, 3> fill_color)
    : center(center), thickness(thickness), radius(radius), color(color), fill(fill), fill_color(fill_color) {}
    Circle()
    : center({0, 0}), thickness(0), radius(0), color({0,0,0}), fill(0), fill_color({0,0,0}) {}
};


struct Color
{
    unsigned char b, g, r;

    Color()
        : b(0), g(0), r(0) {}
    Color(unsigned char r, unsigned char g, unsigned char b)
        : b(b), g(g), r(r) {}
};
