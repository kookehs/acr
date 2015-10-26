// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Window/Event.hpp>

#include "Apex/System/Debug.hpp"
#include "Apex/System/InputHandler.hpp"
#include "Apex/Window/WindowHandler.hpp"

InputHandler::InputHandler() {
    mWindowHandler = NULL;
    mEscapePressed = false;
    mLeftArrowPressed = false;
    mRightArrowPressed = false;
}

InputHandler::InputHandler(WindowHandler* const handler) {
    mWindowHandler = handler;
    mEscapePressed = false;
    mLeftArrowPressed = false;
    mRightArrowPressed = false;
}

InputHandler::~InputHandler() {
}

const bool
InputHandler::escapePressed() const {
    return mEscapePressed;
}

void
InputHandler::escapePressed(const bool status) {
    mEscapePressed = status;
}

const WindowHandler* const
InputHandler::windowHandler() const {
    return mWindowHandler;
}

void
InputHandler::windowHandler(WindowHandler* const handler) {
    mWindowHandler = handler;
}

const bool
InputHandler::leftArrowPressed() const {
    return mLeftArrowPressed;
}

void
InputHandler::leftArrowPressed(const bool status) {
    mLeftArrowPressed = status;
}

void
InputHandler::process(const float time) {
    sf::Event event;

    while (mWindowHandler->pollEvent(&event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                mWindowHandler->close();
            } break;

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Escape: {
                        mEscapePressed = true;
                        Debug::log("InputHandler::process | escaped button pressed");
                    } break;

                    case sf::Keyboard::Left: {
                        mLeftArrowPressed = true;
                        Debug::log("InputHandler::process | left arrow button pressed");
                    } break;

                    case sf::Keyboard::Right: {
                        mRightArrowPressed = true;
                        Debug::log("InputHandler::process | right arrow button pressed");
                    } break;
                }
            } break;

            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                    case sf::Keyboard::Escape: {
                        mEscapePressed = false;
                        Debug::log("InputHandler::process | escaped button released");
                    } break;

                    case sf::Keyboard::Left: {
                        mLeftArrowPressed = false;
                        Debug::log("InputHandler::process | left arrow button released");
                    } break;

                    case sf::Keyboard::Right: {
                        mRightArrowPressed = false;
                        Debug::log("InputHandler::process | right arrow button released");
                    } break;
                }
            } break;
        }
    }
}

const bool
InputHandler::rightArrowPressed() const {
    return mRightArrowPressed;
}

void
InputHandler::rightArrowPressed(const bool status) {
    mRightArrowPressed = status;
}
