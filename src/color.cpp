#include "color.h"
#include <vector>

Color::Color(Colors c){
    
    switch (c)
    {
    case Colors::red:
        hex_values= std::vector<int>({ 0xE1, 0x24, 0x24, 0xFF});
        break;
    case Colors::green:
        hex_values= std::vector<int>({ 0x24, 0xE1, 0x24, 0xFF});
        break;
    case Colors::blue:
        hex_values= std::vector<int>({ 0x24, 0x24, 0xE1, 0xFF});
        break;
    case Colors::orange:
        hex_values= std::vector<int>({ 0xFA, 0x96, 0x05, 0xFF});
        break;
    case Colors::yellow:
        hex_values= std::vector<int>({ 0xE6, 0xE6, 0x1E, 0xFF});
        break;
    case Colors::lblue:
        hex_values= std::vector<int>({ 0x1E, 0xE6, 0xE6, 0xFF});
        break;
    case Colors::pink:
        hex_values= std::vector<int>({ 0xFA, 0x0A, 0xC8, 0xFF});
        break;
    case Colors::purple:
        hex_values= std::vector<int>({ 0xA0, 0x1E, 0xE1, 0xFF});
        break; 
    case Colors::black:
        hex_values= std::vector<int>({ 0x00, 0x00, 0x00, 0xFF});
        break;
    case Colors::white:
    default:
        hex_values= std::vector<int>({ 0xFF, 0xFF, 0xFF, 0xFF});
    }

}