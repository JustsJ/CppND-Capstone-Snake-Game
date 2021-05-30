#include "color.h"

std::vector<int> color::get_hex_values(){
    
    switch (value)
    {
    case colors::red:
        return std::vector<int>({ 0xE1, 0x24, 0x24, 0xFF});
    
    case colors::green:
        return std::vector<int>({ 0x24, 0xE1, 0x24, 0xFF});

    case colors::blue:
        return std::vector<int>({ 0x24, 0x24, 0xE1, 0xFF});
        
    case colors::orange:
        return std::vector<int>({ 0xFA, 0x96, 0x05, 0xFF});
        
    case colors::yellow:
        return std::vector<int>({ 0xE6, 0xE6, 0x1E, 0xFF});
        
    case colors::lblue:
        return std::vector<int>({ 0x1E, 0xE6, 0xE6, 0xFF});

    case colors::pink:
        return std::vector<int>({ 0xFA, 0x0A, 0xC8, 0xFF});

    case colors::purple:
        return std::vector<int>({ 0xA0, 0x1E, 0xE1, 0xFF});
         
    case colors::black:
        return std::vector<int>({ 0x00, 0x00, 0x00, 0xFF});

    case colors::white:
    default:
         return std::vector<int>({ 0xFF, 0xFF, 0xFF, 0xFF});
    }

}