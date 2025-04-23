#include "base.h"
#include "tile.h"
#include "ground.h"
#include "resources.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void renderGround(sf::RenderWindow &window) {
    initResources();

    static sf::Sound clickSound;
    static sf::Vector2i selectedTile(-1, -1);

    const int LEVEL_X = 16;
    const int LEVEL_Y = 16;
    char level[LEVEL_X][LEVEL_Y];

    for (auto & i : level) {
        for (int j = 0; j < LEVEL_Y; j++) {
            i[j] = TILE_EMPTY;
        }
    }
    level[1][1] = TILE_ELIXIR_PUMP;
    level[2][1] = TILE_ELIXIR;
    level[3][1] = TILE_ELIXIR;
    level[4][1] = TILE_ELIXIR;
    level[5][1] = TILE_ELIXIR_STORAGE;

    sf::Vector2i currentTile(-1, -1);

    for (int x = 0; x < LEVEL_X; x++) {
        for (int y = 0; y < LEVEL_Y; y++) {
            renderTile(window, x, y, level, currentTile);
        }
    }

    if (currentTile != selectedTile) {
        if (currentTile.x != -1 && currentTile.y != -1) {
            selectedTile = currentTile;
            clickSound.play();
        }
    }

    if (selectedTile.x != -1 && selectedTile.y != -1) {
        sf::Sprite overlay;
        overlay.setTexture(selectOverlayTexture);
        overlay.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        overlay.setPosition(selectedTile.x*SCALED_TILE_SIZE+GROUND_START_X, selectedTile.y*SCALED_TILE_SIZE);
        window.draw(overlay);
    }
}
