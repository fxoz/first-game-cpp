#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

#include "LevelManager.h"

void renderUi(sf::RenderWindow &window);
void renderFps(sf::RenderWindow &window, int fps);
void renderCoordinates(sf::RenderWindow &window);
void renderTooltip(sf::RenderWindow &window, LevelManager &levelManager);

#endif