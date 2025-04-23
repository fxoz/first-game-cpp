#ifndef BRICK_H
#define BRICK_H

#include "../tilebase.h"

class Brick : public TileBase {
public:
    Brick(sf::Vector2i index)
        : TileBase(index, 0, "Brick", "An empty tile.", "brick")
    {
    }
};

#endif // BRICK_H
