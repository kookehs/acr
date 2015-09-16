// Copyright 2015 Bill Lin. All rights reserved.

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <string>

class Debug {
 public:
    ////////////////
    // Constructors
    ////////////////
    Debug() = default;
    ~Debug() = default;

    ////////////////
    // Accessors
    ////////////////
    static const bool debugMode();

    ////////////////
    // Mutators
    ////////////////
    static void debugMode(const bool status);

    ////////////////
    // Functions
    ////////////////
    static void log(const std::string& message);
    static void logError(const std::string& message);
    static void logException(const std::string& message);
    static void logWarning(const std::string& message);

 private:
    ////////////////
    // Member Data
    ////////////////
    static bool mDebugMode;
};

#endif
