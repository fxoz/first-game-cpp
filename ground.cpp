#include "base.h"
#include "ground.h"
#include "TileBase.h"
#include "tiles/Brick.h"
// #include "tiles/ElixirPump.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "tiles/Elixir.h"
#include "tiles/ElixirPump.h"
#include "tiles/ElixirStorage.h"

using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;

sf::Vector2f getTilePosition(const sf::Vector2i &tileIndex) {
    return {
        tileIndex.x * TILE_SIZE + GROUND_START_X,
        tileIndex.y * TILE_SIZE + GROUND_START_Y
    };
}

void renderGround(sf::RenderWindow &window) {
    auto &resources = ResourceHolder::getInstance();
    auto clickSoundBuffer = resources.getSoundBuffer(FOLDER_ASSETS "sfx/tile.mp3");
    sf::Sound clickSound;
    clickSound.setBuffer(*clickSoundBuffer);

    static sf::Vector2i selectedTile(-1, -1);

    constexpr int LEVEL_X = 16;
    constexpr int LEVEL_Y = 16;

    TileGrid level(LEVEL_Y);
    for (auto &row : level) {
        row.resize(LEVEL_X);
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

    level[1][1] = std::make_unique<ElixirPump>(sf::Vector2i(1, 1));
    level[1][2] = std::make_unique<Elixir>(sf::Vector2i(2, 1));
    level[1][3] = std::make_unique<Elixir>(sf::Vector2i(3, 1));
    level[1][4] = std::make_unique<Elixir>(sf::Vector2i(4, 1));
    level[1][5] = std::make_unique<ElixirStorage>(sf::Vector2i(5, 1));

    for (int y = 0; y < LEVEL_Y; y++) {
        for (int x = 0; x < LEVEL_X; x++) {
            auto &tile = level[y][x];
            tile->render(window);
        }
    }

    if (selectedTile.x != -1 && selectedTile.y != -1) {
        std::cout << "Selected tile: " << selectedTile.x << ", " << selectedTile.y << std::endl;
        clickSound.play();

        sf::Sprite overlay;
        overlay.setTexture(*resources.getTexture(FOLDER_ASSETS "textures/selection.png"));
        overlay.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        overlay.setPosition(getTilePosition(selectedTile));
        window.draw(overlay);
    }
}
