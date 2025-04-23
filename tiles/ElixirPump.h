//
// Created by Lynx on 2025-04-23.
//

#ifndef ELIXIRPUMP_H
#define ELIXIRPUMP_H


#include <string>
#include "../tilebase.h"

class ElixirPump : public TileBase {
public:
    ElixirPump() : TileBase() {
        id = 2;
        name = "Elixir Pump";
        description = "Generates elixir over time.";
        textureName = "elixir-pump";
    }

};


#endif //ELIXIRPUMP_H
