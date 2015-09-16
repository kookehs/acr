// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

#include "Apex/System/ResourceHandler.hpp"

ResourceHandler::~ResourceHandler() {
    for (auto& font : mFontAtlas) delete font.second;
    for (auto& image : mImageAtlas) delete image.second;
    for (auto& texture : mTextureAtlas) delete texture.second;
}

const std::unordered_map<std::string, sf::Font*>&
ResourceHandler::fontAtlas() const {
    return mFontAtlas;
}

const std::unordered_map<std::string, sf::Image*>&
ResourceHandler::imageAtlas() const {
    return mImageAtlas;
}

const std::unordered_map<std::string, sf::Texture*>&
ResourceHandler::textureAtlas() const {
    return mTextureAtlas;
}

void
ResourceHandler::loadFromFile(const unsigned char type, const std::string& id, const std::string& path) {
    switch (type) {
        case Type::Texture: {
            sf::Texture* texture = new sf::Texture();
            texture->loadFromFile(path);
            mTextureAtlas.insert({id, texture});
        }
        break;

        default: {
        }
        break;
    }
}

bool
ResourceHandler::exists(const unsigned char type, const std::string& id) {
    if (type == Type::Font) {
        return false;
    }

    return true;
}
