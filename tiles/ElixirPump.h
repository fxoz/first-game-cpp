//
// Created by Lynx on 2025-04-23.
//

#ifndef ELIXIRPUMP_H
#define ELIXIRPUMP_H


#include <string>
#include "../tilebase.h"

float fanSpinningSpeed = 40;
float fanRotation = 0.f;

class ElixirPump : public TileBase {
public:
    ElixirPump() : TileBase() {
        id = 2;
        name = "Elixir Pump";
        description = "Generates elixir over time.";
        texture = elixirPumpTexture;
    }

    void postRender(sf::RenderWindow &window) override {
        sf::Sprite fanSprite;
        elixirPumpFanTexture.setSmooth(true);
        fanSprite.setTexture(elixirPumpFanTexture);
        fanSprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        fanSprite.setPosition(position.x + TILE_SIZE_HALF,
                              position.y + GROUND_START_Y + TILE_SIZE_HALF);
        fanSprite.setOrigin(0.5f * fanSprite.getLocalBounds().width, 0.5f * fanSprite.getLocalBounds().height);
        fanSprite.rotate(fanRotation);
    }
};


#endif //ELIXIRPUMP_H
