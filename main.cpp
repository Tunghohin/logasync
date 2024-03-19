#include "./sgimglog.h"
#include <iostream>

struct walala {
    int a = 2;
    int b = 3;
    char const* data = "palala";
};

auto operator<<(std::ostream& os, walala const& obj) -> std::ostream& {
    return os << "walala: a: " << obj.a << ", b: " << obj.b
              << ", c: " << obj.data;
}

int main() { std::cout << walala() << std::endl; }
