#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <memory>
#include <SFML/Graphics.hpp>

#include "TileBase.h"
#include "LevelManager.h"

using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;

void renderGround(sf::RenderWindow &window, LevelManager &levelManager);

sf::Vector2f getTilePosition(const sf::Vector2i &tileIndex);
sf::Vector2i getTileIndex(const sf::Vector2f &mousePos);
void initLevel();

#endif
