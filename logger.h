#ifndef _SGIMG_LOGGER_H
#define _SGIMG_LOGGER_H

#include <memory>
#include <string>
#include <vector>

#include "./common.h"
#include "./details/misc/spin_lock.h"
#include "./sinks/sink.h"

namespace sgimg {

class Logger {
public:
    using ptr = Logger*;
    using sptr = std::shared_ptr<Logger>;
    using uptr = std::unique_ptr<Logger>;

    Logger() = default;
    Logger(std::string name) : name_(name) {}
    Logger(std::string name, sinks::sink_sptr sink)
        : name_(name), sinks_{sink} {}

    auto sinks() -> std::vector<sinks::sink_sptr>&;
    auto sinks() const -> std::vector<sinks::sink_sptr> const&;

    constexpr auto level() const noexcept -> sgimg::log_level_t const&;
    constexpr auto name() const noexcept -> std::string const&;

private:
    std::string const name_;
    sgimg::log_level_t const level_{sgimg::LogLevel::INFO};
    std::vector<sinks::sink_sptr> sinks_;
};

inline constexpr auto Logger::level() const noexcept
    -> sgimg::log_level_t const& {
    return this->level_;
}

inline constexpr auto Logger::name() const noexcept -> std::string const& {
    return this->name_;
}

inline auto Logger::sinks() -> std::vector<sinks::sink_sptr>& {
    return this->sinks_;
}

inline auto Logger::sinks() const -> std::vector<sinks::sink_sptr> const& {
    return this->sinks_;
}

} // namespace sgimg

#endif
