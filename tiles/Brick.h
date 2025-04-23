#ifndef BRICK_H
#define BRICK_H

#include "../tilebase.h"

class Brick : public TileBase {
public:
    explicit Brick(const sf::Vector2i& index = sf::Vector2i(0.f, 0.f))
        : TileBase(index, 0, "Brick", "An empty tile.") {
        texture = brickTexture;
    }
};

#endif // BRICK_H
