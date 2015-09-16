// Copyright 2015 Bill Lin. All rights reserved.

#include <string>
#include <unordered_map>
#include <vector>

class Miscellaneous {
 public:
    ////////////////
    // Constructors
    ////////////////

    ////////////////
    // Accessors
    ////////////////

    ////////////////
    // Mutators
    ////////////////

    ////////////////
    // Functions
    ////////////////
    static std::unordered_map<std::string, std::string> loadFromFile(const std::string& path);
    static std::vector<std::string> split(const std::string& input, const char delimiter);
    static void trim(std::string* const input);

 private:
    ////////////////
    // Member Data
    ////////////////
};
