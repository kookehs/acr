// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "Apex/Window/WindowHandler.hpp"

WindowHandler::WindowHandler() {
    initialize();
}

WindowHandler::~WindowHandler() {
    delete mRenderWindow;
}

void
WindowHandler::initialize() {
    mRenderWindow = new sf::RenderWindow();
}

const sf::RenderWindow* const
WindowHandler::renderWindow() const {
    return mRenderWindow;
}

void
WindowHandler::windowClear() {
    mRenderWindow->clear(sf::Color(0, 0, 0));
}

void
WindowHandler::windowClear(const sf::Color& color) {
    mRenderWindow->clear(color);
}

void
WindowHandler::windowClose() {
    mRenderWindow->close();
}

void
WindowHandler::windowCreate(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) {
    mRenderWindow->create(mode, title, style);
    // TODO(kookehs): Find a better way to adjust window position
    // mRenderWindow->setPosition({-9, 0});
}

void
WindowHandler::windowDisplay() {
    mRenderWindow->display();
}

void
WindowHandler::windowDraw(const sf::Sprite& sprite) {
    mRenderWindow->draw(sprite);
}

bool
WindowHandler::windowEvent(sf::Event* const event) {
    return mRenderWindow->pollEvent(*event);
}

bool
WindowHandler::windowIsOpen() {
    return mRenderWindow->isOpen();
}

const sf::Vector2u&
WindowHandler::windowSize() const {
    return mRenderWindow->getSize();
}

void
WindowHandler::windowView(const sf::View& view) {
    mRenderWindow->setView(view);
}
