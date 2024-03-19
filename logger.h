#ifndef _SGIMG_LOGGER_H
#define _SGIMG_LOGGER_H

#include <memory>
#include <string>
#include <vector>

#include "./common.h"
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
    virtual ~Logger() = default;

    auto sinks() -> std::vector<sinks::sink_sptr>&;
    auto sinks() const -> std::vector<sinks::sink_sptr> const&;

    constexpr auto level() const noexcept -> LevelEnum;
    constexpr auto name() const noexcept -> std::string const&;

    auto set_level(LogLevel const&) -> void;

private:
    std::string const name_;
    LogLevel level_{LevelEnum::INFO};
    std::vector<sinks::sink_sptr> sinks_;
};

inline constexpr auto Logger::level() const noexcept -> LevelEnum {
    return static_cast<LevelEnum>(level_.load(std::memory_order_relaxed));
}

inline constexpr auto Logger::name() const noexcept -> std::string const& {
    return this->name_;
}

inline auto Logger::set_level(LogLevel const& level) -> void {
    this->level_.store(level);
}

inline auto Logger::sinks() -> std::vector<sinks::sink_sptr>& {
    return this->sinks_;
}

inline auto Logger::sinks() const -> std::vector<sinks::sink_sptr> const& {
    return this->sinks_;
}

} // namespace sgimg

#endif
