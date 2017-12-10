#include <iostream>
#include <spdlog/spdlog.h>

#include "config.h"

int main() {
    auto logger = spdlog::stdout_logger_mt("console");
    logger->info("OtusCpp version " OTUSCPP_VERNAME " started");

    std::cout << "Hello World!" << std::endl;

    return 0;
}

