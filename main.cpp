#include <chrono>
#include <iostream>

#include <sglogger/logger.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

int main() {
    auto logger = sgimg::log::LoggerImpl("mainlog");
    logger.info("Now: {}", 233);
}
