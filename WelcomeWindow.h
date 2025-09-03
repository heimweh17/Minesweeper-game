#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WelcomeWindow {
public:
    WelcomeWindow(int width, int height);
    std::string run();

private:
    int windowWidth;
    int windowHeight;
    std::string playerName;

    sf::Font font;
    sf::Text titleText;
    sf::Text promptText;
    sf::Text inputText;

    void handleEvent(sf::Event& event, sf::RenderWindow& window, bool& done);
    void updateInputText();
    void draw(sf::RenderWindow& window);
    sf::Text createCenteredText(const std::string& str, unsigned int size, float y, sf::Color color, bool bold = false, bool underline = false);
};