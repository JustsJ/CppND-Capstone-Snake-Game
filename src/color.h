#ifndef COLOR_H
#define COLOR_H

#include <vector>

enum Colors{white, black, red, green, blue, orange, yellow, lblue, pink, purple};

class Color{
    public:
    Color(){};
    Color(Colors);
    Colors value{Colors::black};
    std::vector<int> hex_values;
    std::vector<int> get_hex_values();
};

#endif