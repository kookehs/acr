// Copyright 2015 Bill Lin. All rights reserved.

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Apex/System/Debug.hpp"
#include "Apex/System/Miscellaneous.hpp"

std::unordered_map<std::string, std::string>
Miscellaneous::loadFromFile(const std::string& path) {
    std::unordered_map<std::string, std::string> configurationAtlas;
    std::ifstream configurationFile(path);

    if (!configurationFile.good()) {
        Debug::logError("Miscellaneous::loadFromFile | failed to open given file <" + path + ">");
    } else {
        while (!configurationFile.eof()) {
            std::string line("");
            std::getline(configurationFile, line);
            if (line.empty()) continue;
            auto& values = Miscellaneous::split(line, ':');
            configurationAtlas.insert({values.front(), values.back()});
        }
    }

    return configurationAtlas;
}

std::vector<std::string>
Miscellaneous::split(const std::string& input, const char delimiter) {
    std::vector<std::string> elements;
    std::stringstream inputStream(input);
    std::string value("");

    while (std::getline(inputStream, value, delimiter)) {
        trim(&value);
        elements.push_back(value);
    }

    return elements;
}

void
Miscellaneous::trim(std::string* const input) {
    if (input->length() == 0) return;
    size_t begin = input->find_first_not_of(" ");
    size_t end = input->find_last_not_of(" ");
    if (begin == std::string::npos || end == std::string::npos) return;
    *input = input->substr(begin, end - begin + 1);
}
