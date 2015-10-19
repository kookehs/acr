// Copyright 2015 Bill Lin. All rights reserved.

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
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
    delete mCurrentImage;
    delete mCurrentSprite;
    delete mCurrentTexture;
    delete mHandlers;
    delete mHttpClient;
    delete mTimePerFrame;
}

const std::string&
Root::applicationTitle() const {
    return mApplicationTitle;
}

void
Root::applicationTitle(const std::string& title) {
    mApplicationTitle = title;
}

const std::string&
Root::comicURL() const {
    return mComicURL;
}

void
Root::comicURL(const std::string& url) {
    mComicURL = url;
}

const std::string&
Root::currentComicURL() const {
    return mCurrentComicURL;
}

void
Root::currentComicURL(const std::string& url) {
    mCurrentComicURL = url;
}

const sf::Image* const
Root::currentImage() const {
    return mCurrentImage;
}

void
Root::currentImage(sf::Image* const image) {
    mCurrentImage = image;
}

const sf::Sprite* const
Root::currentSprite() const {
    return mCurrentSprite;
}

void
Root::currentSprite(sf::Sprite* const sprite) {
    mCurrentSprite = sprite;
}

const sf::Texture* const
Root::currentTexture() const {
    return mCurrentTexture;
}

void
Root::currentTexture(sf::Texture* const texture) {
    mCurrentTexture = texture;
}

const Handlers* const
Root::handlers() const {
    return mHandlers;
}

void
Root::handlers(Handlers* const handlers) {
    mHandlers = handlers;
}

const sf::Http* const
Root::httpClient() const {
    return mHttpClient;
}

void
Root::httpClient(sf::Http* const client) {
    mHttpClient = client;
}

const sf::Http::Request* const
Root::httpRequest() const {
    return mHttpRequest;
}

void
Root::httpRequest(sf::Http::Request* const request) {
    mHttpRequest = request;
}
void
Root::initialize() {
    auto& dataAtlas = Miscellaneous::loadFromFile("C:/Apex/Data/Config.ini");
    // TODO(kookehs): Disable debug mode in release version
    Debug::debugMode(std::stoi(dataAtlas.at("DebugMode")));
    mComicURL = dataAtlas.at("ComicURL");
    mServerURL = dataAtlas.at("ServerURL");

    mApplicationTitle = "Project Apex";
    mHandlers = new Handlers();
    mHandlers->windowHandler(new WindowHandler());
    mHandlers->inputHandler(new InputHandler(mHandlers->windowHandler()));

    mTimePerFrame = new sf::Time();
    *mTimePerFrame = sf::seconds(1.0f / std::stoi(dataAtlas.at("FrameRate")));

    unsigned int windowHeight = std::stoi(dataAtlas.at("WindowHeight"));
    unsigned int windowWidth = std::stoi(dataAtlas.at("WindowWidth"));
    // TODO(kookehs): Check whether sf::Style::Resize works as intended on Windows 10
    mHandlers->windowHandler()->windowCreate({windowWidth, windowHeight}, mApplicationTitle, sf::Style::Close);

    mCurrentImage = new sf::Image();
    mCurrentSprite = new sf::Sprite();
    mCurrentTexture = new sf::Texture();
    mHttpClient = new sf::Http(mServerURL);
    mHttpRequest = new sf::Http::Request();
    mHttpRequest->setMethod(sf::Http::Request::Get);
    mHttpRequest->setUri(mComicURL);
    mCurrentComicURL = mComicURL;

    // There are 2 uninitialized accesses cause by the following line
    sf::Http::Response response = mHttpClient->sendRequest(*mHttpRequest);

    if (response.getStatus() == sf::Http::Response::Ok) {
        Debug::log("Response OK");
        std::string body = response.getBody();
        mCurrentImage->loadFromMemory(body.c_str(), body.length());
        mCurrentTexture->loadFromImage(*mCurrentImage, sf::IntRect(0 , 0, 1600, 900));
        mCurrentSprite->setTexture(*mCurrentTexture);
        Debug::log("Image loaded from memory");
    } else {
        Debug::log("Response BAD");
    }
}

void
Root::loadNextPage(const std::string& current) {
    // TODO(kookehs): Handle pages with increasing number of digits
    size_t dotIndex = mCurrentComicURL.find_last_of(".", mCurrentComicURL.length());
    std::string currentPageNumbera = mCurrentComicURL.substr(dotIndex - 3, 3);
    Debug::log(currentPageNumbera);
    char currentPageNumber = mCurrentComicURL[dotIndex - 1];
    char nextPageNumber = currentPageNumber + 1;
    mCurrentComicURL.at(dotIndex - 1) = nextPageNumber;

    mHttpRequest->setUri(mCurrentComicURL);
    sf::Http::Response nextPageResponse = mHttpClient->sendRequest(*mHttpRequest);

    if (nextPageResponse.getStatus() == sf::Http::Response::Ok) {
        Debug::log("Response OK");
        std::string body = nextPageResponse.getBody();
        mCurrentImage->loadFromMemory(body.c_str(), body.length());
        sf::Vector2u windowSize = mHandlers->windowHandler()->windowSize();
        mCurrentTexture->loadFromImage(*mCurrentImage, sf::IntRect(0 , 0, windowSize.x, windowSize.y));
        mCurrentSprite->setTexture(*mCurrentTexture);
    } else {
        Debug::log("Response BAD");
    }
}

void
Root::run() {
    sf::Clock timer;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mHandlers->windowHandler()->windowIsOpen()) {
        sf::Time deltaTime = timer.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > *mTimePerFrame) {
            timeSinceLastUpdate -= *mTimePerFrame;
            mHandlers->inputHandler()->process(mTimePerFrame->asSeconds());
            if (mHandlers->inputHandler()->escapePressed() == true) mHandlers->windowHandler()->windowClose();
            if (mHandlers->inputHandler()->rightArrowPressed() == true) loadNextPage(mCurrentComicURL);
        }

        mHandlers->windowHandler()->windowClear(sf::Color::Black);
        mHandlers->windowHandler()->windowDraw(*mCurrentSprite);
        mHandlers->windowHandler()->windowDisplay();
    }
}

const std::string&
Root::serverURL() const {
    return mServerURL;
}

void
Root::serverURL(const std::string& url) {
    mServerURL = url;
}

const sf::Time* const
Root::timePerFrame() const {
    return mTimePerFrame;
}

void
Root::timePerFrame(sf::Time* const time) {
    mTimePerFrame = time;
}
