// Copyright 2015 Bill Lin. All rights reserved.

#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>

namespace sf {
class Time;
}  // namespace sf

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
    const std::string& comicURL() const;
    const std::string& currentComicURL() const;
    const sf::Image* const currentImage() const;
    const sf::Sprite* const currentSprite() const;
    const sf::Texture* const currentTexture() const;
    const Handlers* const handlers() const;
    const sf::Http* const httpClient() const;
    const sf::Http::Request* const httpRequest() const;
    const std::string& serverURL() const;
    const sf::Time* const timePerFrame() const;

    ////////////////
    // Mutators
    ////////////////
    void applicationTitle(const std::string& title);
    void comicURL(const std::string& url);
    void currentComicURL(const std::string& url);
    void currentImage(sf::Image* const image);
    void currentSprite(sf::Sprite* const sprite);
    void currentTexture(sf::Texture* const texture);
    void handlers(Handlers* const handlers);
    void httpClient(sf::Http* const client);
    void httpRequest(sf::Http::Request* const request);
    void serverURL(const std::string& url);
    void timePerFrame(sf::Time* const time);

    ////////////////
    // Functions
    ////////////////
    void initialize();
    void run();


 private:
    ////////////////
    // Functions
    ////////////////
    void loadNextPage(const std::string& current);

    ////////////////
    // Member Data
    ////////////////
    std::string mApplicationTitle;
    std::string mComicURL;
    std::string mCurrentComicURL;
    sf::Image* mCurrentImage;
    sf::Sprite* mCurrentSprite;
    sf::Texture* mCurrentTexture;
    Handlers* mHandlers;
    sf::Http* mHttpClient;
    sf::Http::Request* mHttpRequest;
    std::string mServerURL;
    sf::Time* mTimePerFrame;
};

#endif
