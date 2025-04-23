#ifndef BACKGROUND_H
#define BACKGROUND_H

#define TILE_EMPTY 0
#define TILE_ELIXIR 1
#define TILE_ELIXIR_PUMP 2
#define TILE_ELIXIR_STORAGE 3

#define TILE_ZOOM 3.f
#define TILE_ZOOM_HALF (TILE_ZOOM / 2.f)

#define TILE_SIZE_UNSCALED 16
#define TILE_SIZE (TILE_SIZE_UNSCALED * TILE_ZOOM)
#define TILE_SIZE_HALF (TILE_SIZE / 2.f)

#define GROUND_START_X 500
#define GROUND_START_Y (1 * TILE_SIZE)

#include <memory>
#include <SFML/Graphics.hpp>

#include "TileBase.h"

using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;
void renderGround(sf::RenderWindow &window);
sf::Vector2f getTilePosition(const sf::Vector2i &tileIndex);

#endif
