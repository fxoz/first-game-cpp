#include "base.h"
#include "background.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define SCALED_TILE_SIZE (TILE_SIZE * TILE_ZOOM)
#define TILE_ZOOM_HALF (TILE_ZOOM / 2.f)

void renderBackground(sf::RenderWindow &window) {
    static sf::Texture brickTexture;
    static sf::Texture selectOverlayTexture;
    static sf::SoundBuffer clickBuffer;
    static sf::Sound clickSound;
    static bool resourcesLoaded = false;

    static sf::Vector2i selectedTile(-1, -1);

    if (!resourcesLoaded) {
        if (!brickTexture.loadFromFile(FOLDER_ASSETS "textures/brick.png")) {
            std::cerr << "Failed to load brick texture!" << std::endl;
            return;
        }

        if (!selectOverlayTexture.loadFromFile(FOLDER_ASSETS "textures/brick-select.png")) {
            std::cerr << "Failed to load selection overlay texture!" << std::endl;
            return;
        }

        if (!clickBuffer.loadFromFile(FOLDER_ASSETS "sfx/click.mp3")) {
            std::cerr << "Failed to load click sound!" << std::endl;
            return;
        }

        clickSound.setBuffer(clickBuffer);
        clickSound.setVolume(20);
        resourcesLoaded = true;
    }

    sf::Vector2i mousePosPixels = sf::Mouse::getPosition(window);
    sf::Vector2i currentTile(-1, -1);

    for (int x = GROUND_START_X; x < DIMENSION_X - SCALED_TILE_SIZE; x += SCALED_TILE_SIZE) {
        for (int y = 0; y < DIMENSION_Y - SCALED_TILE_SIZE; y += SCALED_TILE_SIZE) {
            sf::Sprite sprite;
            sprite.setTexture(brickTexture);
            sprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
            sprite.setPosition(x, y);

            sf::FloatRect bounds = sprite.getGlobalBounds();

            if (bounds.contains(sf::Vector2f(mousePosPixels))) {
                currentTile = sf::Vector2i(x, y);
                sprite.setColor(sf::Color(255, 255, 255, 255));
            } else {
                sprite.setColor(sf::Color(255, 255, 255, 210));
            }

            window.draw(sprite);
        }
    }

    if (currentTile != selectedTile) {
        if (currentTile.x != -1 && currentTile.y != -1) {
            selectedTile = currentTile;
            clickSound.play();
        }
    }

    // Draw selection overlay if a tile is selected
    if (selectedTile.x != -1 && selectedTile.y != -1) {
        sf::Sprite overlay;
        overlay.setTexture(selectOverlayTexture);
        overlay.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        overlay.setPosition(static_cast<float>(selectedTile.x), static_cast<float>(selectedTile.y));
        window.draw(overlay);
    }
}
