// Copyright 2015 Bill Lin. All rights reserved.

#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP

#include <string>

namespace sf {
class Color;
class Event;
class RenderWindow;
class Sprite;
class VideoMode;
class View;
template <typename T>
class Vector2;
typedef Vector2<unsigned int> Vector2u;
typedef unsigned int Uint32;
}  // namespace sf

class WindowHandler {
 public:
    ////////////////
    // Constructors
    ////////////////
    WindowHandler();
    ~WindowHandler();

    ////////////////
    // Accessors
    ////////////////
    const sf::RenderWindow* const renderWindow() const;
    const sf::Vector2u& windowSize() const;

    ////////////////
    // Mutators
    ////////////////

    ////////////////
    // Functions
    ////////////////
    void initialize();
    void windowClear();
    void windowClear(const sf::Color& color);
    void windowClose();
    void windowCreate(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    void windowDisplay();
    void windowDraw(const sf::Sprite& sprite);
    bool windowEvent(sf::Event* const event);
    bool windowIsOpen();
    void windowView(const sf::View& view);

 private:
    ////////////////
    // Member Data
    ////////////////
    sf::RenderWindow* mRenderWindow;
};

#endif
