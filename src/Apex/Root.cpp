// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <string>

#include "Apex/Root.hpp"
#include "Apex/System/Debug.hpp"
#include "Apex/System/Handlers.hpp"
#include "Apex/System/InputHandler.hpp"
#include "Apex/System/Miscellaneous.hpp"
#include "Apex/Window/WindowHandler.hpp"

int
main(int argc, char** argv) {
    Root root;
    root.run();

    return 0;
}

Root::Root() {
    initialize();
}

Root::~Root() {
    delete mHandlers;
}

const std::string&
Root::applicationTitle() const {
    return mApplicationTitle;
}

void
Root::applicationTitle(const std::string& title) {
    mApplicationTitle = title;
}

const Handlers* const
Root::handlers() const {
    return mHandlers;
}

void
Root::handlers(Handlers* const handlers) {
    mHandlers = handlers;
}

void
Root::initialize() {
    auto& dataAtlas = Miscellaneous::loadFromFile("C:/Apex/Data/Config.ini");
    mServerURL = dataAtlas.at("ServerURL");
    Debug::debugMode(std::stoi(dataAtlas.at("DebugMode")));

    mApplicationTitle = "Project Apex";
    mHandlers = new Handlers();
    mHandlers->windowHandler(new WindowHandler());
    mHandlers->inputHandler(new InputHandler(mHandlers->windowHandler()));
    // TODO(kookehs): Check whether sf::Style::Resize works as intended on Windows 10
    mHandlers->windowHandler()->windowCreate(sf::VideoMode::getDesktopMode(), mApplicationTitle, sf::Style::Close);
}

void
Root::run() {
    while (mHandlers->windowHandler()->windowIsOpen()) {
        // TODO(kookehs): Calculate elapsed time
        mHandlers->inputHandler()->process(1.0f);

        if (mHandlers->inputHandler()->escapePressed() == true) {
            Debug::log("Root::run | window is closing");
            mHandlers->windowHandler()->windowClose();
        }

        mHandlers->windowHandler()->windowClear(sf::Color::Black);
        mHandlers->windowHandler()->windowDisplay();
    }
}
