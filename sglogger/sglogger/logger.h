#pragma once

#include <memory>
#include <type_traits>

#include <sglogger/logger_base.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace sgimg::log {

template <typename LoggerImpl>
class Logger {
    static_assert(!std::is_same_v<LoggerImpl, LoggerImpl>,
                  "Need a LoggerImpl!");
};

template <>
class Logger<spdlog::sinks::rotating_file_sink_mt> final
    : public log::LoggerBase {
public:
    Logger(std::string const&);

    template <typename... Args>
    auto trace(std::string const&, Args&&...) -> void;

    template <typename... Args>
    auto debug(std::string const&, Args&&...) -> void;

    template <typename... Args>
    auto info(std::string const&, Args&&...) -> void;

    template <typename... Args>
    auto warn(std::string const&, Args&&...) -> void;

    template <typename... Args>
    auto error(std::string const&, Args&&...) -> void;

    template <typename... Args>
    auto log(log::LogLevel, std::string const&, Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto trace_forward(Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto debug_forward(Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto info_forward(Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto warn_forward(Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto error_forward(Args&&...) -> void;

    // Do not use it if it is not a performance bottleneck. This method improves
    // performance but reduces portability.
    template <typename... Args>
    auto log_forward(log::LogLevel, Args&&...) -> void;

private:
    std::shared_ptr<spdlog::logger> inner_;
};

inline Logger<spdlog::sinks::rotating_file_sink_mt>::Logger(
    std::string const& name)
    : log::LoggerBase(name),
      inner_(spdlog::rotating_logger_mt(name_, "./log/log.sglog",
                                        1024 * 1024 * 64, 0)) {
    this->inner_->set_level(spdlog::level::trace);
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::trace(std::string const& fmt,
                                                    Args&&... args) -> void {
    this->inner_->trace(
        std::move(sgimg::log::format(fmt, std::forward<Args>(args)...)));
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::debug(std::string const& fmt,
                                                    Args&&... args) -> void {
    this->inner_->debug(
        std::move(sgimg::log::format(fmt, std::forward<Args>(args)...)));
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::info(std::string const& fmt,
                                                   Args&&... args) -> void {
    this->inner_->info(
        std::move(sgimg::log::format(fmt, std::forward<Args>(args)...)));
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::warn(std::string const& fmt,
                                                   Args&&... args) -> void {
    this->inner_->warn(
        std::move(sgimg::log::format(fmt, std::forward<Args>(args)...)));
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::error(std::string const& fmt,
                                                    Args&&... args) -> void {
    this->inner_->error(
        std::move(sgimg::log::format(fmt, std::forward<Args>(args)...)));
}

template <typename... Args>
inline auto Logger<spdlog::sinks::rotating_file_sink_mt>::log(
    log::LogLevel lv, std::string const& fmt, Args&&... args) -> void {
    if (this->should_log(lv)) {
        switch (lv) {
        case LogLevel::trace:
            return this->trace(fmt, std::forward<Args>(args)...);
        case LogLevel::debug:
            return this->debug(fmt, std::forward<Args>(args)...);
        case LogLevel::info:
            return this->info(fmt, std::forward<Args>(args)...);
        case LogLevel::warn:
            return this->warn(fmt, std::forward<Args>(args)...);
        case LogLevel::error:
            return this->error(fmt, std::forward<Args>(args)...);
        };
    } else
        return;
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::trace_forward(Args&&... args)
    -> void {
    this->inner_->trace(std::forward<Args>(args)...);
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::debug_forward(Args&&... args)
    -> void {
    this->inner_->debug(std::forward<Args>(args)...);
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::info_forward(Args&&... args)
    -> void {
    this->inner_->info(std::forward<Args>(args)...);
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::warn_forward(Args&&... args)
    -> void {
    this->inner_->warn(std::forward<Args>(args)...);
}

template <typename... Args>
inline auto
Logger<spdlog::sinks::rotating_file_sink_mt>::error_forward(Args&&... args)
    -> void {
    this->inner_->error(std::forward<Args>(args)...);
}

template <typename... Args>
inline auto Logger<spdlog::sinks::rotating_file_sink_mt>::log_forward(
    log::LogLevel lv, Args&&... args) -> void {
    if (this->should_log(lv)) {
        switch (lv) {
        case LogLevel::trace:
            return this->trace_forward(std::forward<Args>(args)...);
        case LogLevel::debug:
            return this->debug_forward(std::forward<Args>(args)...);
        case LogLevel::info:
            return this->info_forward(std::forward<Args>(args)...);
        case LogLevel::warn:
            return this->warn_forward(std::forward<Args>(args)...);
        case LogLevel::error:
            return this->error_forward(std::forward<Args>(args)...);
        };
    } else
        return;
}

using LoggerImpl = Logger<spdlog::sinks::rotating_file_sink_mt>;

} // namespace sgimg::log
