//
// Created by Lynx on 2025-04-25.
//

#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <memory>
#include <vector>
#include "TileBase.h"
#include "tiles/Brick.h"
#include "tiles/Elixir.h"
#include "tiles/ElixirPump.h"
#include "tiles/ElixirClump.h"
#include "tiles/ElixirStorage.h"

constexpr int LEVEL_X = 16;
constexpr int LEVEL_Y = 16;

class LevelManager {
public:
    using TileGrid = std::vector<std::vector<std::unique_ptr<TileBase>>>;

private:
    TileGrid level;

public:
    void initLevel() {
        level.clear();
        level.resize(LEVEL_Y);
        for (int y = 0; y < LEVEL_Y; ++y) {
            level[y].resize(LEVEL_X);
            for (int x = 0; x < LEVEL_X; ++x) {
                level[y][x] = std::make_unique<Brick>(sf::Vector2i(x, y));
            }
        }

        if (LEVEL_Y > 1 && LEVEL_X > 5) {
            level[0][1] = std::make_unique<ElixirClump>(sf::Vector2i(1, 0));
            level[0][2] = std::make_unique<ElixirClump>(sf::Vector2i(2, 0));
            level[1][1] = std::make_unique<ElixirPump>(sf::Vector2i(1, 1));
            level[1][2] = std::make_unique<Elixir>(sf::Vector2i(2, 1));
            level[1][3] = std::make_unique<Elixir>(sf::Vector2i(3, 1));
            level[1][4] = std::make_unique<Elixir>(sf::Vector2i(4, 1));
            level[1][5] = std::make_unique<ElixirStorage>(sf::Vector2i(5, 1), 0.5f);
        }
    }

    TileBase* getTileAt(const sf::Vector2i &tileIndex) {
        if (tileIndex.x < 0 || tileIndex.x >= LEVEL_X ||
            tileIndex.y < 0 || tileIndex.y >= LEVEL_Y ||
            level.empty() || level[tileIndex.y].empty()) {
            return nullptr;
        }
        return level[tileIndex.y][tileIndex.x].get();
    }

    const TileGrid& getLevel() const {
        return level;
    }

    void setTileAt(const sf::Vector2i &tileIndex, std::unique_ptr<TileBase> newTile) {
        if (tileIndex.x < 0 || tileIndex.x >= LEVEL_X ||
            tileIndex.y < 0 || tileIndex.y >= LEVEL_Y) {
            return;
        }
        level[tileIndex.y][tileIndex.x] = std::move(newTile);
    }
};

#endif