#pragma once

#include <memory>
#include <string>

#include <sglogger/common.h>
#include <sglogger/formatter.h>

namespace sgimg::log {

class LoggerBase {
public:
    LoggerBase() = default;
    LoggerBase(std::string const&);
    virtual ~LoggerBase() = default;

    auto should_log(log::LogLevel lv) const -> bool {
        return lv >= static_cast<log::LogLevel>(
                         this->level_.load(std::memory_order_relaxed));
    };

    auto name() -> std::string const& { return this->name_; }

    auto level() const -> log::LogLevel {
        return static_cast<log::LogLevel>(
            this->level_.load(std::memory_order_relaxed));
    }

    auto set_level(log::LogLevel lv) -> void {
        this->level_.store(static_cast<int>(lv));
    }

protected:
    std::string const name_;
    log::log_level_t level_{static_cast<int>(log::LogLevel::info)};
};

inline LoggerBase::LoggerBase(std::string const& name) : name_(name) {}

} // namespace sgimg::log
