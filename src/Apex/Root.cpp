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
    delete mHttpClient;
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
Root::comicURI() const {
    return mComicURI;
}

void
Root::comicURI(const std::string& uri) {
    mComicURI = uri;
}

std::string
Root::computePageURI(const char offset) {
    // TODO(kookehs): Check for last pages
    size_t dotIndex = mCurrentPageURI.find_last_of(".", mCurrentPageURI.length());
    std::string prefix = mCurrentPageURI.substr(0, dotIndex - 3);
    std::string suffix = mCurrentPageURI.substr(dotIndex, mCurrentPageURI.length());
    std::string currentPageNumber = mCurrentPageURI.substr(dotIndex - 3, 3);
    std::string followingPageNumber = std::to_string(std::stoi(currentPageNumber) + offset);
    size_t nextPageLength = followingPageNumber.length();
    for (size_t i = 0; i < 3 - nextPageLength; ++i) followingPageNumber = "0" + followingPageNumber;

    return prefix + followingPageNumber + suffix;
}

const std::string&
Root::currentPageURI() const {
    return mCurrentPageURI;
}

void
Root::currentPageURI(const std::string& uri) {
    mCurrentPageURI = uri;
}

void
Root::displayNextPage() {
    mImageContainer.at(0) = mImageContainer.at(1);
    mImageContainer.at(1) = mImageContainer.at(2);
    mSpriteContainer.at(0) = mSpriteContainer.at(1);
    mSpriteContainer.at(1) = mSpriteContainer.at(2);
    mTextureContainer.at(0) = mTextureContainer.at(1);
    mTextureContainer.at(1) = mTextureContainer.at(2);
}

void
Root::displayPreviousPage() {
    mImageContainer.at(2) = mImageContainer.at(1);
    mImageContainer.at(1) = mImageContainer.at(0);
    mSpriteContainer.at(2) = mSpriteContainer.at(1);
    mSpriteContainer.at(1) = mSpriteContainer.at(0);
    mTextureContainer.at(2) = mTextureContainer.at(1);
    mTextureContainer.at(1) = mTextureContainer.at(0);
}

const Handlers&
Root::handlers() const {
    return mHandlers;
}

void
Root::handlers(const Handlers& handlers) {
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

const sf::Http::Request&
Root::httpRequest() const {
    return mHttpRequest;
}

void
Root::httpRequest(const sf::Http::Request& request) {
    mHttpRequest = request;
}

const std::vector<sf::Image>&
Root::imageContainer() const {
    return mImageContainer;
}

void
Root::imageContainer(const std::vector<sf::Image>& container) {
    mImageContainer = container;
}

void
Root::initialize() {
    auto& dataAtlas = Miscellaneous::loadFromFile("C:/Apex/Data/Config.ini");
    // TODO(kookehs): Disable debug mode in release version
    Debug::debugMode(std::stoi(dataAtlas.at("DebugMode")));
    mComicURI = dataAtlas.at("ComicURI");
    mServerURL = dataAtlas.at("ServerURL");

    mApplicationTitle = "Project Apex";
    mHandlers.windowHandler(new WindowHandler());
    mHandlers.inputHandler(new InputHandler(mHandlers.windowHandler()));

    mTimePerFrame = sf::seconds(1.0f / std::stoi(dataAtlas.at("FrameRate")));

    unsigned int windowHeight = std::stoi(dataAtlas.at("WindowHeight"));
    unsigned int windowWidth = std::stoi(dataAtlas.at("WindowWidth"));
    // TODO(kookehs): Check whether sf::Style::Resize works as intended on Windows 10
    mHandlers.windowHandler()->create({windowWidth, windowHeight}, mApplicationTitle, sf::Style::Close);

    mHttpClient = new sf::Http(mServerURL);
    mHttpRequest.setMethod(sf::Http::Request::Get);
    mHttpRequest.setUri(mComicURI);
    mCurrentPageURI = mComicURI;

    loadPage(Page::Current);
    loadPage(Page::Next);
    loadPage(Page::Previous);
}

void
Root::loadPage(const char offset) {
    if (offset < -1 || offset > 1) return;
    std::string followingPageURI = computePageURI(offset);
    mHttpRequest.setUri(followingPageURI);
    sf::Http::Response followingPageResponse = mHttpClient->sendRequest(mHttpRequest);

    if (followingPageResponse.getStatus() == sf::Http::Response::Ok) {
        Debug::log("Response OK");
        std::string body = followingPageResponse.getBody();
        sf::Image followingPageImage;
        followingPageImage.loadFromMemory(body.c_str(), body.length());
        sf::Vector2u windowSize = mHandlers.windowHandler()->size();
        sf::Texture followingPageTexture;
        followingPageTexture.loadFromImage(followingPageImage, sf::IntRect(0, 0, windowSize.x, windowSize.y));
        sf::Sprite followingPageSprite;
        followingPageSprite.setTexture(followingPageTexture);

        if (offset == -1) {
            mPreviousPageURI = followingPageURI;
            mImageContainer.at(0) = followingPageImage;
            mSpriteContainer.at(0) = followingPageSprite;
            mTextureContainer.at(0) = followingPageTexture;
        } else if (offset == 0) {
            mCurrentPageURI = followingPageURI;
            mImageContainer.at(1) = followingPageImage;
            mSpriteContainer.at(1) = followingPageSprite;
            mTextureContainer.at(1) = followingPageTexture;
        } else if (offset == 1) {
            mNextPageURI = followingPageURI;
            mImageContainer.at(2) = followingPageImage;
            mSpriteContainer.at(2) = followingPageSprite;
            mTextureContainer.at(2) = followingPageTexture;
        }
    } else {
        // TODO(kookehs): Display an error
        Debug::log("Response BAD");
    }
}

const std::string&
Root::nextPageURI() const {
    return mNextPageURI;
}

void
Root::nextPageURI(const std::string& uri) {
    mNextPageURI = uri;
}

const std::string&
Root::previousPageURI() const {
    return mPreviousPageURI;
}

void
Root::previousPageURI(const std::string& uri) {
    mPreviousPageURI = uri;
}

void
Root::run() {
    // TODO(kookehs): Consider event-based rendering
    sf::Clock timer;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mHandlers.windowHandler()->isOpen()) {
        sf::Time deltaTime = timer.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > mTimePerFrame) {
            timeSinceLastUpdate -= mTimePerFrame;
            mHandlers.inputHandler()->process(mTimePerFrame.asSeconds());
            if (mHandlers.inputHandler()->escapePressed() == true) mHandlers.windowHandler()->close();

            if (mHandlers.inputHandler()->leftArrowPressed() == true) {
                displayPreviousPage();
                loadPage(Page::Previous);
            }

            if (mHandlers.inputHandler()->rightArrowPressed() == true) {
                displayNextPage();
                loadPage(Page::Next);
            }
        }

        mHandlers.windowHandler()->clear(sf::Color::Black);
        mHandlers.windowHandler()->draw(mSpriteContainer.at(1));
        mHandlers.windowHandler()->display();
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

const std::vector<sf::Sprite>&
Root::spriteContainer() const {
    return mSpriteContainer;
}

void
Root::spriteContainer(const std::vector<sf::Sprite>& container) {
    mSpriteContainer = container;
}

const std::vector<sf::Texture>&
Root::textureContainer() const {
    return mTextureContainer;
}

void
Root::textureContainer(const std::vector<sf::Texture>& container) {
    mTextureContainer = container;
}

const sf::Time&
Root::timePerFrame() const {
    return mTimePerFrame;
}

void
Root::timePerFrame(const sf::Time& time) {
    mTimePerFrame = time;
}
