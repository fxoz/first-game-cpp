#ifndef TILEBASE_H
#define TILEBASE_H

#include <iostream>
#include <string>
#include <memory>
#include "ResourceManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

class TileBase {
protected:
    char id;
    bool selected;
    sf::Vector2i index;
    sf::Vector2f position;
    std::string name;
    std::string description;
    std::shared_ptr<sf::Texture> texture;

public:
    virtual ~TileBase() = default;

    TileBase(sf::Vector2i index, char id, std::string name, std::string description, const std::string &textureKey)
        : id(id), selected(false), index(index),
          name(std::move(name)), description(std::move(description))
    {
        position = {
            index.x * TILE_SIZE + GROUND_START_X,
            index.y * TILE_SIZE + GROUND_START_Y
        };

        std::string texturePath = std::string(FOLDER_ASSETS "textures/tiles/") + textureKey + ".png";

        texture = ResourceHolder::getInstance().getTexture(texturePath);
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

    void setSelected(bool selected) {
        this->selected = selected;
    }

    virtual void render(sf::RenderWindow &window) {
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(position);
        sprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        window.draw(sprite);

        postRender(window);
    }

    virtual sf::FloatRect getRectangle() const {
        sf::Sprite sprite;
        sprite.setTexture(*texture);
        sprite.setPosition(position);
        sprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));
        return sprite.getGlobalBounds();
    }

    virtual void postRender(sf::RenderWindow &window) {
    }
};

#endif // TILEBASE_H
