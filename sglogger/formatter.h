#pragma once

#include <functional>
#include <sstream>
#include <vector>

namespace sgimg::log {

using arg_builder_t = std::function<void(std::ostream&)>;

inline auto format_impl(std::string const& fmt,
                        std::vector<arg_builder_t> const& arg_builders)
    -> std::string {
    std::stringstream ss;
    size_t start_pos = 0;
    for (auto&& arg_builder : arg_builders) {
        std::size_t const pos = fmt.find("{}", start_pos);
        if (pos == std::string::npos)
            break;
        ss << fmt.substr(start_pos, pos - start_pos);
        arg_builder(ss);
        start_pos = pos + 2; // +2 to skip brackets placeholder
    }
    ss << fmt.substr(start_pos);
    return ss.str();
}

template <typename Arg>
inline auto format_arg(Arg const& arg) -> std::function<void(std::ostream&)> {
    return [&arg](std::ostream& ss) { ss << arg; };
}

template <typename... Args>
inline auto format(std::string const& fmt, Args const&... args) -> std::string {
    return format_impl(fmt, {format_arg(args)...});
}

} // namespace sgimg::log
