#ifndef ELIXIRCLUMP_H
#define ELIXIRCLUMP_H

#include "../tilebase.h"

class ElixirClump : public TileBase {
public:
    explicit ElixirClump(sf::Vector2i index)
        : TileBase(index, 4, "Elixir Clump", "An elixir clump.", "elixir-clump")
    {
    }
};

#endif
