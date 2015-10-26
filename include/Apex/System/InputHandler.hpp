// Copyright 2015 Bill Lin. All rights reserved.

#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

class WindowHandler;

class InputHandler {
 public:
    ////////////////
    // Constructors
    ////////////////
    InputHandler();
    explicit InputHandler(WindowHandler* const handler);
    ~InputHandler();

    ////////////////
    // Accessors
    ////////////////
    const bool escapePressed() const;
    const WindowHandler* const windowHandler() const;
    const bool leftArrowPressed() const;
    const bool rightArrowPressed() const;

    ////////////////
    // Mutators
    ////////////////
    void escapePressed(const bool status);
    void windowHandler(WindowHandler* const handler);
    void leftArrowPressed(const bool status);
    void rightArrowPressed(const bool status);

    ////////////////
    // Functions
    ////////////////
    void process(const float time);

 private:
    ////////////////
    // Member Data
    ////////////////
    bool mEscapePressed;
    WindowHandler* mWindowHandler;
    bool mLeftArrowPressed;
    bool mRightArrowPressed;
};

#endif
