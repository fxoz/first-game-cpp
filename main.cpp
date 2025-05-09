#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "SFML/Audio/Listener.hpp"
#include "cmake-build-debug/_deps/sfml-src/src/SFML/Audio/AudioDevice.hpp"

#include "ui.h"
#include "base.h"
#include "ground.h"
#include "LevelManager.h"
#include "settings.h"

#define FPS_MAX 360
#define FPS_IDLE 30
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define VSYNC_ENABLED false

LevelManager globalLevelManager;

void onKey(sf::RenderWindow &window, sf::Event event, int screenWidth, int screenHeight, bool &isFullscreen, bool &isViewSettings) {
    if (event.key.code == sf::Keyboard::F11) {
        isFullscreen = !isFullscreen;
        if (isFullscreen) {
            window.create(sf::VideoMode::getDesktopMode(), WINDOW_NAME, sf::Style::Fullscreen);
        } else {
            window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
        }
    }

    if (event.key.code == sf::Keyboard::Escape) {
        isViewSettings = !isViewSettings;
    }
}

void handleEvents(sf::RenderWindow &window, sf::Event event, int screenWidth, int screenHeight, bool &isFullscreen, bool &isViewSettings) {
    if (event.type == sf::Event::Closed)
        window.close();

    if (event.type == sf::Event::LostFocus) {
        window.setFramerateLimit(FPS_IDLE);
        sf::Listener::setGlobalVolume(0.0f);
    }

    if (event.type == sf::Event::GainedFocus) {
        window.setFramerateLimit(FPS_MAX);
        sf::Listener::setGlobalVolume(100.0f);
    }

    if (event.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }

    if (event.type == sf::Event::KeyReleased) {
        onKey(window, event, screenWidth, screenHeight, isFullscreen, isViewSettings);
    }
}

int main() {
    if (!std::filesystem::exists("assets")) {
        std::cerr << "Assets folder not found!" << std::endl;
        return 1;
    }

    int screenWidth = sf::VideoMode::getDesktopMode().width;
    int screenHeight = sf::VideoMode::getDesktopMode().height;

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    window.setFramerateLimit(FPS_MAX);
    window.setVerticalSyncEnabled(VSYNC_ENABLED);

    globalLevelManager.initLevel();

    int fps = 0;
    float fpsLastUpdatedTime = -1;
    float framesThisSecond = 0;

    bool isFullscreen = false;
    bool isViewSettings = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvents(window, event, screenWidth, screenHeight, isFullscreen, isViewSettings);
        }

        if (clock.getElapsedTime().asSeconds() - fpsLastUpdatedTime > 1.f) {
            fps = (int)framesThisSecond / (int)(clock.getElapsedTime().asSeconds() - fpsLastUpdatedTime);
            framesThisSecond = 0;
            fpsLastUpdatedTime = clock.getElapsedTime().asSeconds();
        }

        framesThisSecond++;

        window.clear();
        if (isViewSettings) {
            renderSettings(window);
            window.display();
            return 0;
        }

        renderGround(window, globalLevelManager);
        renderUi(window);
        renderFps(window, fps);
        renderCoordinates(window);
        renderTooltip(window, globalLevelManager);
        window.display();
    }

    return 0;
}