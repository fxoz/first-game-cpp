//
// Created by Lynx on 2025-04-23.
//

#ifndef RESOURCES_H
#define RESOURCES_H

#include "SFML/Audio/SoundBuffer.hpp"

extern sf::Font font;
extern sf::SoundBuffer clickSoundBuffer;

extern sf::Texture brickTexture;
extern sf::Texture selectOverlayTexture;
extern sf::Texture elixirTexture;
extern sf::Texture elixirPumpTexture;
extern sf::Texture elixirPumpFanTexture;
extern sf::Texture elixirStorageTexture;

void initResources();

#endif //RESOURCES_H
