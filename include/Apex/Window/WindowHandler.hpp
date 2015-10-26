// Copyright 2015 Bill Lin. All rights reserved.

#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

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
    const sf::RenderWindow& const renderWindow() const;
    const sf::Vector2u& size() const;

    ////////////////
    // Mutators
    ////////////////

    ////////////////
    // Functions
    ////////////////
    void clear();
    void clear(const sf::Color& color);
    void close();
    void create(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    void display();
    void draw(const sf::Sprite& sprite);
    bool isOpen();
    bool pollEvent(sf::Event* const event);
    void view(const sf::View& view);

 private:
    ////////////////
    // Member Data
    ////////////////
    sf::RenderWindow mRenderWindow;
};

#endif
