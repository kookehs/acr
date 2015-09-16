// Copyright 2015 Bill Lin. All rights reserved.

#ifndef HANDLERS_HPP
#define HANDLERS_HPP

class InputHandler;
class ResourceHandler;
class WindowHandler;

class Handlers {
 public:
    ////////////////
    // Constructors
    ////////////////
    Handlers();
    ~Handlers();

    ////////////////
    // Accessors
    ////////////////
    InputHandler* const inputHandler() const;
    ResourceHandler* const resourceHandler() const;
    WindowHandler* const windowHandler() const;

    ////////////////
    // Mutators
    ////////////////
    void inputHandler(InputHandler* const handler);
    void resourceHandler(ResourceHandler* const handler);
    void windowHandler(WindowHandler* const handler);

    ////////////////
    // Functions
    ////////////////

 private:
    ////////////////
    // Member Data
    ////////////////
    InputHandler* mInputHandler;
    ResourceHandler* mResourceHandler;
    WindowHandler* mWindowHandler;
};

#endif
