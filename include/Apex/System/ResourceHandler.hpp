// Copyright 2015 Bill Lin. All rights reserved.

#ifndef RESOURCEHANDLER_HPP
#define RESOURCEHANDLER_HPP

#include <string>
#include <unordered_map>

namespace sf {
class Font;
class Image;
class Texture;
}  // namespace sf

namespace Type {
enum {
    Font = 0,
    Image = 1,
    Texture = 2
};
}

class ResourceHandler {
 public:
    ////////////////
    // Constructors
    ////////////////
    ResourceHandler() = default;
    ~ResourceHandler();

    ////////////////
    // Accessors
    ////////////////
    const std::unordered_map<std::string, sf::Font*>& fontAtlas() const;
    const std::unordered_map<std::string, sf::Image*>& imageAtlas() const;
    const std::unordered_map<std::string, sf::Texture*>& textureAtlas() const;

    ////////////////
    // Mutators
    ////////////////

    ////////////////
    // Functions
    ////////////////
    bool exists(const unsigned char type, const std::string& id);
    void loadFromFile(const unsigned char type, const std::string& id, const std::string& path);

 private:
    ////////////////
    // Member Data
    ////////////////
    std::unordered_map<std::string, sf::Font*> mFontAtlas;
    std::unordered_map<std::string, sf::Image*> mImageAtlas;
    std::unordered_map<std::string, sf::Texture*> mTextureAtlas;
};

#endif
