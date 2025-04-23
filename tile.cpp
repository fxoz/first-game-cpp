#include "base.h"
#include "tile.h"
#include "ground.h"
#include "resources.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Mouse.hpp"

namespace sf {
    class RenderWindow;
}

float fanSpinningSpeed = 40;
float fanRotation = 0.f;

void renderTile(sf::RenderWindow &window, int x, int y, char level[16][16], sf::Vector2i &currentTile) {
    initResources();
    static sf::Clock clock;

    sf::Sprite sprite;
    sf::Sprite fanSprite;
    sprite.setTexture(brickTexture);

    bool isElixirPump = false;

    if (level[x][y] == TILE_ELIXIR_PUMP) {
        isElixirPump = true;

        sprite.setTexture(elixirPumpTexture);
        elixirPumpFanTexture.setSmooth(true);
        fanSprite.setTexture(elixirPumpFanTexture);
        fanSprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        fanSprite.setPosition(x * SCALED_TILE_SIZE + GROUND_START_X + 0.5f * SCALED_TILE_SIZE,
                              y * SCALED_TILE_SIZE + GROUND_START_Y + 0.5f * SCALED_TILE_SIZE);
        fanSprite.setOrigin(0.5f * fanSprite.getLocalBounds().width, 0.5f * fanSprite.getLocalBounds().height);
        fanSprite.rotate(fanRotation);
        sprite.setPosition(x * SCALED_TILE_SIZE + GROUND_START_X, y * SCALED_TILE_SIZE + GROUND_START_Y);
    }

    if (level[x][y] == TILE_ELIXIR) {
        sprite.setTexture(elixirTexture);
    }

    sf::RectangleShape capacityIndicator({0, 0});
    if (level[x][y] == TILE_ELIXIR_STORAGE) {
        sprite.setTexture(elixirStorageTexture);

        float capacity = 1.0f;
        float capacityWidth = SCALED_TILE_SIZE * capacity;

        capacityIndicator.setSize({capacityWidth, 4});
        capacityIndicator.setFillColor(sf::Color(255, 255, 255, 200));
        capacityIndicator.setPosition(x * SCALED_TILE_SIZE + GROUND_START_X, (y+1) * SCALED_TILE_SIZE-4 + GROUND_START_Y);
    }

    sprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
    sprite.setPosition(x * SCALED_TILE_SIZE + GROUND_START_X, y * SCALED_TILE_SIZE + GROUND_START_Y);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::Vector2i mousePosPixels = sf::Mouse::getPosition(window);
    bool isHovered = bounds.contains(sf::Vector2f(mousePosPixels));

    sprite.setColor(sf::Color(255, 255, 255, 255));

    if (isHovered) {
        currentTile = sf::Vector2i(x, y);
        sprite.setColor(sf::Color(230, 230, 230, 230));
    }

    window.draw(sprite);
    if (isElixirPump) {
        float deltaTime = clock.restart().asSeconds();
        fanRotation += fanSpinningSpeed * deltaTime;

        if (fanRotation > 360.f) {
            fanRotation = 0.f;
        }
        window.draw(fanSprite);
    }

    if (level[x][y] == TILE_ELIXIR_STORAGE) {
        window.draw(capacityIndicator);
    }

    if (isHovered) {
        float tooltipWidth = SCALED_TILE_SIZE*6;
        float outlineThickness = 2;

        sf::RectangleShape background;
        background.setSize(sf::Vector2f(tooltipWidth, 2*SCALED_TILE_SIZE));
        background.setFillColor(sf::Color(50, 50, 75, 200));
        background.setPosition((x * SCALED_TILE_SIZE + GROUND_START_X - tooltipWidth) - 2*outlineThickness, (y-1) * SCALED_TILE_SIZE + GROUND_START_Y);
        background.setOutlineColor(sf::Color(255, 255, 255, 255));
        background.setOutlineThickness(outlineThickness);
        window.draw(background);

        sf::Text text;
        text.setFont(font);
        text.setString("x" + std::to_string(x) + " y" + std::to_string(y));
        text.setCharacterSize(24);
        text.setPosition((x * SCALED_TILE_SIZE + GROUND_START_X) - tooltipWidth, (y-1) * SCALED_TILE_SIZE + GROUND_START_Y -5);
        text.setFillColor(sf::Color::White);
        window.draw(text);
    }
}
