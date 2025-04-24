#ifndef ELIXIRPUMP_H
#define ELIXIRPUMP_H

#include <SFML/Graphics.hpp>
#include "../base.h"
#include "../tilebase.h"
#include <memory>
#include <cmath>

class ElixirPump : public TileBase {
public:
    explicit ElixirPump(sf::Vector2i index)
        : TileBase(index, 2, "Elixir Pump", "An elixir pump.", "elixir-pump"),
          m_fanSpinningSpeed(90.f)
    {
        m_elixirPumpFanTexture = ResourceHolder::getInstance().getTexture(FOLDER_ASSETS "textures/tiles/elixir-pump-fan.png");
        if (m_elixirPumpFanTexture) {
            m_elixirPumpFanTexture->setSmooth(true);
        }
    }

    void postRender(sf::RenderWindow &window) override {
        sf::Sprite fanSprite;
        if (m_elixirPumpFanTexture) {
            fanSprite.setTexture(*m_elixirPumpFanTexture);
        }
        fanSprite.scale(sf::Vector2f(TILE_ZOOM_HALF, TILE_ZOOM_HALF));

        float rotation = std::fmod(m_fanSpinningSpeed * s_animationClock.getElapsedTime().asSeconds(), 360.f);
        fanSprite.setRotation(rotation);

        fanSprite.setPosition(position.x + TILE_SIZE_HALF, position.y + TILE_SIZE_HALF);
        fanSprite.setOrigin(fanSprite.getLocalBounds().width / 2.f, fanSprite.getLocalBounds().height / 2.f);

        window.draw(fanSprite);
    }

private:
    float m_fanSpinningSpeed;
    std::shared_ptr<sf::Texture> m_elixirPumpFanTexture;
    inline static sf::Clock s_animationClock;
};

#endif // ELIXIRPUMP_H
