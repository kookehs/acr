// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Graphics/Sprite.hpp>

#include <string>

#include "Apex/System/Debug.hpp"
#include "Apex/Window/WindowHandler.hpp"

WindowHandler::WindowHandler() {
}

WindowHandler::~WindowHandler() {
}

const sf::RenderWindow& const
WindowHandler::renderWindow() const {
    return mRenderWindow;
}

void
WindowHandler::clear() {
    mRenderWindow.clear(sf::Color(0, 0, 0));
}

void
WindowHandler::clear(const sf::Color& color) {
    mRenderWindow.clear(color);
}

void
WindowHandler::close() {
    Debug::log("WindowHandler::close | window is closing");
    mRenderWindow.close();
}

void
WindowHandler::create(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) {
    mRenderWindow.create(mode, title, style);
    // TODO(kookehs): Find a better way to adjust window position
    // mRenderWindow.setPosition({-9, 0});
}

void
WindowHandler::display() {
    mRenderWindow.display();
}

void
WindowHandler::draw(const sf::Sprite& sprite) {
    mRenderWindow.draw(sprite);
}

bool
WindowHandler::isOpen() {
    return mRenderWindow.isOpen();
}

bool
WindowHandler::pollEvent(sf::Event* const event) {
    return mRenderWindow.pollEvent(*event);
}

const sf::Vector2u&
WindowHandler::size() const {
    return mRenderWindow.getSize();
}

void
WindowHandler::view(const sf::View& view) {
    mRenderWindow.setView(view);
}
