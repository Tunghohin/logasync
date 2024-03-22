#include <iostream>

#include "sglogger/logger.h"
#include "spdlog/sinks/rotating_file_sink.h"

struct walala {
    int a = 2;
    int b = 3;
    char const* data = "palala";
};

auto operator<<(std::ostream& os, walala const& obj) -> std::ostream& {
    return os << "walala: a: " << obj.a << ", b: " << obj.b
              << ", c: " << obj.data;
}

int main() {
    auto logger = sgimg::log::Logger<spdlog::sinks::rotating_file_sink>("MAIN");
}
