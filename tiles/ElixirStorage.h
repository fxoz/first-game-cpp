#ifndef ELIXIRSTORAGE_H
#define ELIXIRSTORAGE_H

#include "../tilebase.h"

class ElixirStorage : public TileBase {
protected:
    float capacity;

public:
    ElixirStorage(sf::Vector2i index, float capacity)
        : TileBase(index, 3, "Elixir Storage", "Stores elixir.", "elixir-storage"),
          capacity(capacity)
    {
    }

    void postRender(sf::RenderWindow &window) override {
        float capacityWidth = TILE_SIZE * capacity;
        sf::RectangleShape capacityIndicator;
        capacityIndicator.setSize({capacityWidth, 4});
        capacityIndicator.setFillColor(sf::Color(255, 255, 255, 200));
        capacityIndicator.setPosition(
            index.x * TILE_SIZE + GROUND_START_X,
            (index.y + 1) * TILE_SIZE - 4 + GROUND_START_Y
        );
        window.draw(capacityIndicator);
    }
};

#endif
