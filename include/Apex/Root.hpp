// Copyright 2015 Bill Lin. All rights reserved.

#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>

class Handlers;

class Root {
 public:
    ////////////////
    // Constructors
    ////////////////
    Root();
    ~Root();

    ////////////////
    // Accessors
    ////////////////
    const std::string& applicationTitle() const;
    const Handlers* const handlers() const;

    ////////////////
    // Mutators
    ////////////////
    void applicationTitle(const std::string& title);
    void handlers(Handlers* const handlers);

    ////////////////
    // Functions
    ////////////////
    void initialize();
    void run();

 private:
    ////////////////
    // Member Data
    ////////////////
    std::string mApplicationTitle;
    Handlers* mHandlers;
    std::string mServerURL;
};

#endif
