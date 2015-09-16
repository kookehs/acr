// Copyright 2015 Bill Lin. All rights reserved.

#include "Apex/System/Handlers.hpp"
#include "Apex/System/InputHandler.hpp"
#include "Apex/System/ResourceHandler.hpp"
#include "Apex/Window/WindowHandler.hpp"

Handlers::Handlers() {
    mInputHandler = NULL;
    mResourceHandler = NULL;
    mWindowHandler = NULL;
}

Handlers::~Handlers() {
    delete mInputHandler;
    delete mResourceHandler;
    delete mWindowHandler;
}

InputHandler* const
Handlers::inputHandler() const {
    return mInputHandler;
}

void
Handlers::inputHandler(InputHandler* const handler) {
    mInputHandler = handler;
}

ResourceHandler* const
Handlers::resourceHandler() const {
    return mResourceHandler;
}

void
Handlers::resourceHandler(ResourceHandler* const handler) {
    mResourceHandler = handler;
}

WindowHandler* const
Handlers::windowHandler() const {
    return mWindowHandler;
}

void
Handlers::windowHandler(WindowHandler* const handler) {
    mWindowHandler = handler;
}
