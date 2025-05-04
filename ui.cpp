#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "base.h"
#include "ground.h"
#include "LevelManager.h"

inline sf::Font& getUIFont() {
    return *ResourceHolder::getInstance().getFont(FOLDER_ASSETS "fonts/ui.ttf");
}

inline void drawText(sf::RenderWindow& window, const std::string &str, unsigned size, const sf::Vector2f &pos, sf::Color color = sf::Color::White) {
    sf::Text text(str, getUIFont(), size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(pos);
    window.draw(text);
}

inline sf::Sprite createSprite(const std::string &texturePath, const sf::Vector2f &pos, const sf::Vector2f &scale) {
    sf::Sprite sprite(*ResourceHolder::getInstance().getTexture(texturePath));
    sprite.setPosition(pos);
    sprite.setScale(scale);
    return sprite;
}

void renderUi(sf::RenderWindow &window) {
    window.draw(createSprite(FOLDER_ASSETS "textures/ui/cash.png", {1 * REM, 1 * REM}, {2.f, 2.f}));
    drawText(window, "Balance: 1000", 32, {4 * REM, .75f * REM});
}

void renderFps(sf::RenderWindow &window, int fps) {
    sf::Text fpsText("FPS: " + std::to_string(fps), getUIFont(), 26);
    fpsText.setFillColor(sf::Color::White);
    auto bounds = fpsText.getLocalBounds();
    fpsText.setPosition({ window.getSize().x - bounds.width - 0.5f * REM, 1 * REM - bounds.height });
    window.draw(fpsText);
}

void renderCoordinates(sf::RenderWindow &window) {
    auto tileIndex = getTileIndex(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    TileBase* tile = (LevelManager{}).getTileAt(tileIndex);
    if (!tile) {
        return;
    }
    
    sf::Text coordsText("X: " + std::to_string(tileIndex.x) + " Y: " + std::to_string(tileIndex.y), getUIFont(), 26);
    coordsText.setFillColor(sf::Color::White);
    auto bounds = coordsText.getLocalBounds();
    coordsText.setPosition({ window.getSize().x - bounds.width - 0.5f * REM, window.getSize().y - bounds.height - 1 * REM });
    window.draw(coordsText);
}

void renderTooltip(sf::RenderWindow &window, LevelManager &levelManager) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    auto tile = levelManager.getTileAt(getTileIndex(mousePos));
    if (!tile || tile->getName() == "Brick") {
        return;
    }

    sf::Text title(tile->getName(), getUIFont(), 26);
    title.setFillColor(sf::Color(255, 215, 0));
    sf::Text description(tile->getDescription(), getUIFont(), 20);
    description.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = title.getLocalBounds();
    sf::FloatRect descBounds = description.getLocalBounds();

    const float margin = REM;
    const float spacing = 0.5f * REM;

    float tooltipWidth = std::max(titleBounds.width, descBounds.width) + 3 * margin;
    float tooltipHeight = titleBounds.height + descBounds.height + spacing + 3 * margin;

    sf::RectangleShape background(sf::Vector2f(tooltipWidth, tooltipHeight));
    background.setFillColor(sf::Color(20, 20, 20, 200));
    sf::Vector2f tooltipPos(mousePos.x, mousePos.y - tooltipHeight);
    background.setPosition(tooltipPos);

    title.setPosition(tooltipPos.x + 1.5f * margin, tooltipPos.y + 0.5f * margin);
    description.setPosition(tooltipPos.x + 1.5f * margin, tooltipPos.y + margin + titleBounds.height + spacing);

    window.draw(background);
    window.draw(title);
    window.draw(description);
}

