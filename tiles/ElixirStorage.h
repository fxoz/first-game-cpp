#ifndef ELIXIRSTORAGE_H
#define ELIXIRSTORAGE_H

#include "../tilebase.h"

class ElixirStorage : public TileBase {
public:
    explicit ElixirStorage(sf::Vector2i index)
        : TileBase(index, 3, "Elixir Storage", "Stores elixir.", "elixir-storage")
    {
    }
};

#endif
