#ifndef TILEBASE_H
#define TILEBASE_H

#include <iostream>
#include <string>
#include <memory>
#include "base.h"
//#include "ground.h"
#include "ResourceManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#define TILE_SIZE_UNSCALED 16
#define TILE_SIZE (TILE_SIZE_UNSCALED * TILE_ZOOM)
#define TILE_SIZE_HALF (TILE_SIZE / 2.f)
#define GROUND_START_X 500
#define GROUND_START_Y (1 * TILE_SIZE)
#define TILE_ZOOM 3.f
#define TILE_ZOOM_HALF (TILE_ZOOM / 2.f)

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

    bool isSelected() const { return selected; }
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2i getIndex() const { return index; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }

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
