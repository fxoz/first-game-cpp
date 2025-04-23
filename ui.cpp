#include <SFML/Graphics.hpp>

#include "ui.h"
#include "base.h"

void renderUi(sf::RenderWindow &window) {
    sf::Texture uiIconCash;
    uiIconCash.loadFromFile(FOLDER_ASSETS "textures/cash.png");

    sf::Sprite uiIconCashSprite;
    uiIconCashSprite.scale(sf::Vector2f(2.f, 2.f));
    uiIconCashSprite.setTexture(uiIconCash);
    uiIconCashSprite.setPosition(1*REM, 1*REM);

    window.draw(uiIconCashSprite);

    sf::Text uiTextBalance;
    sf::Font font = getFont();
    uiTextBalance.setFont(font);
    uiTextBalance.setString("Balance: 1000");
    uiTextBalance.setCharacterSize(32);
    uiTextBalance.setPosition(4*REM, 10);
    uiTextBalance.setFillColor(sf::Color::White);
    uiTextBalance.setStyle(sf::Text::Bold);

    window.draw(uiTextBalance);
}

void renderFps(sf::RenderWindow &window, int fps) {
    static sf::Text uiTextFps;
    static sf::Font font = getFont();

    uiTextFps.setFont(font);
    uiTextFps.setCharacterSize(26);
    sf::FloatRect bounds = uiTextFps.getLocalBounds();
    uiTextFps.setPosition(window.getSize().x - bounds.width - .5f*REM, 1*REM - bounds.height);
    uiTextFps.setFillColor(sf::Color::White);
    uiTextFps.setString("FPS: " + std::to_string(fps));
    window.draw(uiTextFps);
}