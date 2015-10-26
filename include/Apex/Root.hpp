// Copyright 2015 Bill Lin. All rights reserved.

#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

#include "Apex/System/Handlers.hpp"

namespace sf {
class Time;
}  // namespace sf

namespace Page {
enum {
    Previous = -1,
    Current,
    Next
};
}

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
    const std::string& comicURI() const;
    const std::string& currentPageURI() const;
    const Handlers& handlers() const;
    const sf::Http* const httpClient() const;
    const sf::Http::Request& httpRequest() const;
    const std::vector<sf::Image>& imageContainer() const;
    const std::string& nextPageURI() const;
    const std::string& previousPageURI() const;
    const std::string& serverURL() const;
    const std::vector<sf::Sprite>& spriteContainer() const;
    const std::vector<sf::Texture>& textureContainer() const;
    const sf::Time& timePerFrame() const;

    ////////////////
    // Mutators
    ////////////////
    void applicationTitle(const std::string& title);
    void comicURI(const std::string& uri);
    void currentPageURI(const std::string& uri);
    void handlers(const Handlers& handlers);
    void httpClient(sf::Http* const client);
    void httpRequest(const sf::Http::Request& request);
    void imageContainer(const std::vector<sf::Image>& container);
    void nextPageURI(const std::string& uri);
    void previousPageURI(const std::string& uri);
    void serverURL(const std::string& url);
    void spriteContainer(const std::vector<sf::Sprite>& container);
    void textureContainer(const std::vector<sf::Texture>& container);
    void timePerFrame(const sf::Time& time);

    ////////////////
    // Functions
    ////////////////
    void initialize();
    void run();


 private:
    ////////////////
    // Functions
    ////////////////
    std::string computePageURI(const char offset);
    void displayNextPage();
    void displayPreviousPage();
    void loadPage(const char offset);

    ////////////////
    // Member Data
    ////////////////
    std::string mApplicationTitle;
    std::string mComicURI;
    std::string mCurrentPageURI;
    Handlers mHandlers;
    sf::Http* mHttpClient;
    sf::Http::Request mHttpRequest;
    std::vector<sf::Image> mImageContainer;
    std::string mNextPageURI;
    std::string mPreviousPageURI;
    std::string mServerURL;
    std::vector<sf::Sprite> mSpriteContainer;
    std::vector<sf::Texture> mTextureContainer;
    sf::Time mTimePerFrame;
};

#endif
