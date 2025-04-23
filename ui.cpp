#include <SFML/Graphics.hpp>

#include "ui.h"
#include "base.h"

#include "ResourceManager.h"

void renderUi(sf::RenderWindow &window) {
    sf::Texture uiIconCash = *ResourceHolder::getInstance().getTexture(FOLDER_ASSETS "textures/ui/cash.png");

    sf::Sprite uiIconCashSprite;
    uiIconCashSprite.scale(sf::Vector2f(2.f, 2.f));
    uiIconCashSprite.setTexture(uiIconCash);
    uiIconCashSprite.setPosition(1*REM, 1*REM);

    window.draw(uiIconCashSprite);

    sf::Text uiTextBalance;
    sf::Font font = *ResourceHolder::getInstance().getFont(FOLDER_ASSETS "fonts/ui.ttf");
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
    static sf::Font font = *ResourceHolder::getInstance().getFont(FOLDER_ASSETS "fonts/ui.ttf");

    uiTextFps.setFont(font);
    uiTextFps.setCharacterSize(26);
    sf::FloatRect bounds = uiTextFps.getLocalBounds();
    uiTextFps.setPosition(window.getSize().x - bounds.width - .5f*REM, 1*REM - bounds.height);
    uiTextFps.setFillColor(sf::Color::White);
    uiTextFps.setString("FPS: " + std::to_string(fps));
    window.draw(uiTextFps);
}