// Copyright 2015 Bill Lin. All rights reserved.

#include <iostream>
#include <string>

#include "Apex/System/Debug.hpp"

bool Debug::mDebugMode = false;

const bool
Debug::debugMode() {
    return mDebugMode;
}

void
Debug::debugMode(const bool status) {
    mDebugMode = status;
}

void
Debug::log(const std::string& message) {
    if (mDebugMode == false) return;
    std::cout << "[INFO] " << message << std::endl;
}

void
Debug::logError(const std::string& message) {
    if (mDebugMode == false) return;
    std::cout << "[ERROR] " << message << std::endl;
}

void
Debug::logException(const std::string& message) {
    if (mDebugMode == false) return;
    std::cout << "[EXCEPTION] " << message << std::endl;
}

void
Debug::logWarning(const std::string& message) {
    if (mDebugMode == false) return;
    std::cout << "[WARNING] " << message << std::endl;
}
