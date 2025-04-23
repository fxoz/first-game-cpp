#include "base.h"

#include <cstdio>
#include <iostream>

#include "SFML/Graphics/Font.hpp"

sf::Font uiFont;
bool fontLoaded = false;

sf::Font getFont() {
    if (!fontLoaded) {
        uiFont.setSmooth(false);
        if (!uiFont.loadFromFile(FOLDER_ASSETS "fonts/ui.ttf")) {
            perror("Error loading font");
        }
    }
    fontLoaded = true;
    return uiFont;
}
