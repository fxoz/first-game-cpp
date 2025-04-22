#include <SFML/Graphics.hpp>

#include "base.h"
#include "background.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(DIMENSIONS), "My New Game");
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        renderBackground(window);

        // ------------------------------------

        sf::Texture uiIconCash;
        uiIconCash.loadFromFile(FOLDER_ASSETS "textures/cash.png");

        sf::Sprite uiIconCashSprite;
        uiIconCashSprite.scale(sf::Vector2f(2.f, 2.f));
        uiIconCashSprite.setTexture(uiIconCash);
        uiIconCashSprite.setPosition(1 REM, 1 REM);

        window.draw(uiIconCashSprite);

        sf::Text uiTextBalance;
        sf::Font font;
        font.setSmooth(false);
        if (!font.loadFromFile(FOLDER_ASSETS "fonts/pixelify.ttf")) {
            perror("Error loading font");
        }
        uiTextBalance.setFont(font);
        uiTextBalance.setString("Balance: 1000");
        uiTextBalance.setCharacterSize(32);
        uiTextBalance.setPosition(4 REM, .75f REM);
        uiTextBalance.setFillColor(sf::Color::White);
        uiTextBalance.setStyle(sf::Text::Bold);

        window.draw(uiTextBalance);

        // ------------------------------------
        sf::Cursor cursor;
        if (cursor.loadFromSystem(sf::Cursor::Hand))
            window.setMouseCursor(cursor);

        window.display();
    }

    return 0;
}