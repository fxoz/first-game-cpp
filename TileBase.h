#ifndef TILEBASE_H
#define TILEBASE_H

#include <iostream>
#include <string>
#include <utility>

#include "resources.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

class TileBase {
protected:
    char id;
    bool selected{false};
    sf::Vector2i index;
    sf::Vector2f position;
    sf::Texture texture;
    std::string name;
    std::string description;

public:
    virtual ~TileBase() = default;

    TileBase(const sf::Vector2i &index,
             char id,
             std::string name,
             std::string description)
        : index(index),
          id(id),
          name(std::move(name)),
          description(std::move(description))
    {
        position = {
            index.x * TILE_SIZE + GROUND_START_X,
            index.y * TILE_SIZE + GROUND_START_Y
        };
    }

    void setPosition(const sf::Vector2f &newPosition) {
        position = newPosition;
    }

    sf::Vector2f getPosition() const {
        return position;
    }

    sf::Vector2i getIndex() const {
        return index;
    }

    bool isSelected() const {
        return selected;
    }

    virtual void render(sf::RenderWindow &window) {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        window.draw(sprite);

        postRender(window);
    }

    virtual void postRender(sf::RenderWindow &window) {}
};

#endif // TILEBASE_H
