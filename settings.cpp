#include "settings.h"

#include <cmath>
#include <iostream>

#include "base.h"
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

float valueIdleFps = 30;
float valueMaxFps  = 60;
float valueVolume  = 50;
bool isFullscreen  = false;
bool isVSync      = false;
bool isShowFps    = false;

float addOptionRange(sf::RenderWindow &window, float y,
                     const std::string &title,
                     const std::string &description,
                     const std::string &valueSuffix,
                     float min, float max, float step, float &value,
                     const sf::Font &font) {

    const float sliderWidth  = 250;
    const float sliderHeight = 30;
    const float baseX        = window.getSize().x / 2 - 24 * REM;
    const float sliderX      = baseX + 30 * REM;
    const float titleY       = y + 1 * REM;
    const float descY        = y + 3 * REM;
    const float sliderY      = y + 2 * REM;
    const float valueMargin  = 15;
    const float blockSpacing = 4 * REM;

    sf::Text titleText(title, font, 24);
    titleText.setPosition(baseX, titleY);
    titleText.setFillColor(sf::Color::White);
    window.draw(titleText);

    sf::Text descriptionText(description, font, 18);
    descriptionText.setPosition(baseX, descY);
    descriptionText.setFillColor(sf::Color(255, 255, 255, 150));
    window.draw(descriptionText);

    static sf::Texture sliderBgTexture;
    sliderBgTexture.loadFromFile(FOLDER_ASSETS "textures/slider-bg.png");
    sf::Sprite sliderBg;
    sliderBg.setTexture(sliderBgTexture);
    sliderBg.setPosition(sliderX, sliderY);
    window.draw(sliderBg);

    float ratio = (value - min) / (max - min);
    sf::RectangleShape sliderFill({ sliderWidth * ratio, sliderHeight });
    sliderFill.setFillColor(sf::Color(255, 255, 255, 30));
    sliderFill.setPosition(sliderX, sliderY);
    window.draw(sliderFill);

    static sf::Texture sliderHandleTexture;
    sliderHandleTexture.loadFromFile(FOLDER_ASSETS "textures/slider-handle.png");
    sf::Sprite sliderHandle;
    sliderHandle.setTexture(sliderHandleTexture);
    sliderHandle.setPosition(sliderX + sliderWidth * ratio - 5, sliderY - 6);
    window.draw(sliderHandle);

    sf::Vector2i mousePosPixels = sf::Mouse::getPosition(window);

    sf::FloatRect bounds = sliderBg.getGlobalBounds();

    bounds.left -= 10;
    bounds.top -= 10;
    bounds.width += 50;
    bounds.height += 50;

    if (bounds.contains(sf::Vector2f(mousePosPixels))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            float mouseX = static_cast<float>(mousePosPixels.x);
            float newValue = min + ((mouseX - sliderX) / sliderWidth) * (max - min);
            newValue = std::round(newValue / step) * step;
            if (newValue < min) newValue = min;
            if (newValue > max) newValue = max;
            value = newValue;
        }
    }

    sf::Text valueText(std::to_string(static_cast<int>(value)), font, 26);
    valueText.setPosition(sliderX + sliderWidth + valueMargin + 5, sliderY);
    valueText.setFillColor(sf::Color(255, 255, 255, 255));
    window.draw(valueText);

    return titleText.getLocalBounds().height +
           descriptionText.getLocalBounds().height + blockSpacing;
}

float addOptionCheck(sf::RenderWindow &window, float y,
                     const std::string &title,
                     const std::string &description,
                     bool &value,
                     const sf::Font &font) {

    const float baseX        = window.getSize().x / 2 - 24 * REM;
    const float titleY       = y + 1 * REM;
    const float descY        = y + 3 * REM;
    const float checkY       = y + 2 * REM;
    const float valueMargin  = 15;
    const float blockSpacing = 4 * REM;

    sf::Text titleText(title, font, 24);
    titleText.setPosition(baseX, titleY);
    titleText.setFillColor(sf::Color::White);
    window.draw(titleText);

    sf::Text descriptionText(description, font, 18);
    descriptionText.setPosition(baseX, descY);
    descriptionText.setFillColor(sf::Color(255, 255, 255, 150));
    window.draw(descriptionText);

    static sf::Texture checkTexture;
    checkTexture.loadFromFile(value ? FOLDER_ASSETS "textures/yes.png" : FOLDER_ASSETS "textures/no.png");
    sf::Sprite checkSprite;
    checkSprite.setTexture(checkTexture);
    checkSprite.setScale(2, 2);
    checkSprite.setPosition(baseX + 30 * REM, checkY);
    window.draw(checkSprite);

    sf::Vector2i mousePosPixels = sf::Mouse::getPosition(window);

    sf::FloatRect bounds = checkSprite.getGlobalBounds();
    bounds.left -= 10;
    bounds.top -= 10;
    bounds.width += 50;
    bounds.height += 50;

    static bool wasMouseButtonPressed = false;

    if (bounds.contains(sf::Vector2f(mousePosPixels))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !wasMouseButtonPressed) {
            value = !value;
            wasMouseButtonPressed = true;

        } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            wasMouseButtonPressed = false;
        }
    }


    return titleText.getLocalBounds().height +
           descriptionText.getLocalBounds().height + blockSpacing;
}

void renderSettings(sf::RenderWindow &window) {
    const float headerY = 4 * REM;
    sf::Font font = getFont();

    sf::Text settingsText("SETTINGS", font, 42);
    settingsText.setStyle(sf::Text::Bold);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition((window.getSize().x - settingsText.getLocalBounds().width) / 2, headerY);
    window.draw(settingsText);

    float currentY = 10 * REM;
    currentY += addOptionRange(window, currentY, "Max FPS", "Maximum frames per second.", "FPS", 1, 60, 5, valueMaxFps, font);
    currentY += addOptionRange(window, currentY, "Idle FPS", "Frames per second when the window is not focused.", "FPS", 1, 60, 5, valueIdleFps, font);
    currentY += addOptionRange(window, currentY, "Volume", "Sound volume.", "%", 0, 100, 1, valueVolume, font);
    currentY += addOptionCheck(window, currentY, "Fullscreen", "Enable fullscreen mode.", isFullscreen, font);
    currentY += addOptionCheck(window, currentY, "VSync", "Enable vertical sync.", isVSync, font);
    currentY += addOptionCheck(window, currentY, "Show FPS", "Display frames per second.", isShowFps, font);
}
