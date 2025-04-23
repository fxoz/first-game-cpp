//
// Created by Lynx on 2025-04-23.
//

#ifndef TILE_H
#define TILE_H

#define TILE_EMPTY 0
#define TILE_ELIXIR 1
#define TILE_ELIXIR_PUMP 2
#define TILE_ELIXIR_STORAGE 3

#define SCALED_TILE_SIZE (TILE_SIZE * TILE_ZOOM)
#define TILE_ZOOM_HALF (TILE_ZOOM / 2.f)

#include "SFML/Graphics/RenderWindow.hpp"

void renderTile(sf::RenderWindow &window, int x, int y, char level[16][16], sf::Vector2i &currentTile);

#endif //TILE_H
