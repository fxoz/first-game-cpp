#include "base.h"
#include "ground.h"
#include "resources.h"
#include "TileBase.h"
#include "tiles/Brick.h"
// #include "tiles/ElixirPump.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <vector>

using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;

sf::Vector2f getTilePosition(const sf::Vector2i &tileIndex) {
    return {
        tileIndex.x * TILE_SIZE + GROUND_START_X,
        tileIndex.y * TILE_SIZE + GROUND_START_Y
    };
}

void renderGround(sf::RenderWindow &window) {
    initResources();

    static sf::Sound clickSound;
    static sf::Vector2i selectedTile(-1, -1);

    constexpr int LEVEL_X = 16;
    constexpr int LEVEL_Y = 16;

    TileGrid level(LEVEL_X);
    for (auto &row : level) {
        row.resize(LEVEL_Y);
    }

    int y = 0;
    for (auto &row : level) {
        int x = 0;
        for (auto &tile : row) {
            sf::Vector2i tileIndex(x, y);
            tile = std::make_unique<Brick>(tileIndex);
            x++;
        }
        y++;
    }

    for (int x = 0; x < LEVEL_X; x++) {
        for (int y = 0; y < LEVEL_Y; y++) {
            sf::Vector2i tileIndex(x, y);
            auto &tile = level[x][y];
            tile->render(window);
        }
    }

    if (selectedTile.x != -1 && selectedTile.y != -1) {
        std::cout << "Selected tile: " << selectedTile.x << ", " << selectedTile.y << std::endl;
        clickSound.play();

        sf::Sprite overlay;
        overlay.setTexture(selectOverlayTexture);
        overlay.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        overlay.setPosition(getTilePosition(selectedTile));
        window.draw(overlay);
    }
}
