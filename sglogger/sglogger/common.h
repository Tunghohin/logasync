#pragma once

#include <atomic>

namespace sgimg::log {

using log_level_t = std::atomic<int>;

enum class LogLevel : int {
    trace = 0,
    debug = 1,
    info = 2,
    warn = 3,
    error = 4,
    off = 5,
};

inline auto to_c_str(LogLevel lv) -> char const* {
    switch (lv) {
    case LogLevel::trace:
        return "trace";
    case LogLevel::debug:
        return "debug";
    case LogLevel::info:
        return "info";
    case LogLevel::warn:
        return "warn";
    case LogLevel::error:
        return "error";
    case LogLevel::off:
        return "off";
    };
}

} // namespace sgimg::log
