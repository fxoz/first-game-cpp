//
// Created by Lynx on 2025-04-23.
//

#include "base.h"
#include "resources.h"
#include "SFML/Audio/SoundBuffer.hpp"

sf::Font font;
sf::SoundBuffer clickSoundBuffer;

sf::Texture brickTexture;
sf::Texture selectOverlayTexture;
sf::Texture elixirTexture;
sf::Texture elixirPumpTexture;
sf::Texture elixirPumpFanTexture;
sf::Texture elixirStorageTexture;

bool resourcesLoaded = false;

void initResources() {
    if (resourcesLoaded)
        return;

    if (!brickTexture.loadFromFile(FOLDER_ASSETS "textures/brick.png"))
        perror("Failed to load brick texture!");

    if (!selectOverlayTexture.loadFromFile(FOLDER_ASSETS "textures/brick-select.png"))
        perror("Failed to load select overlay texture!");

    if (!elixirTexture.loadFromFile(FOLDER_ASSETS "textures/elixir.png"))
        perror("Failed to load elixir texture!");

    if (!elixirStorageTexture.loadFromFile(FOLDER_ASSETS "textures/elixir-storage.png"))
        perror("Failed to load elixir storage texture!");

    if (!elixirPumpTexture.loadFromFile(FOLDER_ASSETS "textures/elixir-pump.png"))
        perror("Failed to load elixir pump texture!");

    if (!elixirPumpFanTexture.loadFromFile(FOLDER_ASSETS "textures/elixir-pump-fan.png"))
        perror("Failed to load elixir pump fan texture!");

    if (!clickSoundBuffer.loadFromFile(FOLDER_ASSETS "sfx/click.mp3"))
        perror("Failed to load click sound!");

    font = getFont();

    resourcesLoaded = true;
}