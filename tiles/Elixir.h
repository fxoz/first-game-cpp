#ifndef ELIXIR_H
#define ELIXIR_H

#include "../tilebase.h"

class Elixir : public TileBase {
public:
    explicit Elixir(sf::Vector2i index)
        : TileBase(index, 1, "Elixir", "An elixir tile.", "elixir")
    {
    }
};

#endif
