#include <vector>

class color{
    public:
    enum colors{red, green, blue, orange, yellow, lblue, pink, purple, black, white};
    colors value{colors::black};
    std::vector<int> get_hex_values();
};