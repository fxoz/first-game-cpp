#include "base.h"
#include "ground.h"
#include "TileBase.h"
#include "tiles/Brick.h"
#include "tiles/Elixir.h"
#include "tiles/ElixirPump.h"
#include "tiles/ElixirStorage.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <vector>

constexpr int LEVEL_X = 16;
constexpr int LEVEL_Y = 16;

using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;

TileGrid level;
sf::Vector2i currentTile(-1, -1);

void initLevel() {
    level.resize(LEVEL_Y);
    for (int y = 0; y < LEVEL_Y; ++y) {
        level[y].resize(LEVEL_X);
        for (int x = 0; x < LEVEL_X; ++x) {
            level[y][x] = std::make_unique<Brick>(sf::Vector2i(x, y));
        }
    }
    level[1][1] = std::make_unique<ElixirPump>(sf::Vector2i(1, 1));
    level[1][2] = std::make_unique<Elixir>(sf::Vector2i(2, 1));
    level[1][3] = std::make_unique<Elixir>(sf::Vector2i(3, 1));
    level[1][4] = std::make_unique<Elixir>(sf::Vector2i(4, 1));
    level[1][5] = std::make_unique<ElixirStorage>(sf::Vector2i(5, 1), 0.5f);
}

sf::Vector2f getTilePosition(const sf::Vector2i &tileIndex) {
    return {
        tileIndex.x * TILE_SIZE + GROUND_START_X,
        tileIndex.y * TILE_SIZE + GROUND_START_Y
    };
}

sf::Vector2i getTileIndex(const sf::Vector2f &mousePos) {
    return {
        static_cast<int>((mousePos.x - GROUND_START_X) / TILE_SIZE),
        static_cast<int>((mousePos.y - GROUND_START_Y) / TILE_SIZE)
    };
}

TileBase* getTileAt(const sf::Vector2i &tileIndex) {
    if (tileIndex.x < 0 || tileIndex.x >= LEVEL_X ||
        tileIndex.y < 0 || tileIndex.y >= LEVEL_Y ||
        level.empty() || level[tileIndex.y].empty()) {
        return nullptr;
        }
    return level[tileIndex.y][tileIndex.x].get();
}

void playClickSound() {
    auto &resources = ResourceHolder::getInstance();
    static sf::Sound clickSound;
    static bool initialized = false;
    if (!initialized) {
        clickSound.setBuffer(*resources.getSoundBuffer(FOLDER_ASSETS "sfx/tile.mp3"));
        initialized = true;
    }
    clickSound.play();
}

void renderGround(sf::RenderWindow &window) {
    auto &resources = ResourceHolder::getInstance();
    static sf::Vector2i selectedTile(-1, -1);

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    for (int y = 0; y < LEVEL_Y; ++y) {
        for (int x = 0; x < LEVEL_X; ++x) {
            level[y][x]->setSelected(false);
        }
    }

    for (int y = 0; y < LEVEL_Y; ++y) {
        for (int x = 0; x < LEVEL_X; ++x) {
            auto &tile = level[y][x];
            if (tile->getRectangle().contains(mousePos)) {
                currentTile = sf::Vector2i(x, y);
                tile->setSelected(true);
                if (currentTile != selectedTile) {
                    playClickSound();
                    selectedTile = currentTile;
                }
            }
            tile->render(window);
        }
    }

    if (selectedTile.x != -1 && selectedTile.y != -1) {
        sf::Sprite overlay;
        overlay.setTexture(*resources.getTexture(FOLDER_ASSETS "textures/ui/selection.png"));
        overlay.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        overlay.setPosition(getTilePosition(selectedTile));
        window.draw(overlay);
    }
}
