#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Board.h"

class GameWindow {
private:
    sf::RenderWindow window;
    Board board;

    std::map<std::string, sf::Texture> textureMap;
    std::map<std::string, sf::Sprite> buttons;

    sf::Font font;
    sf::Text timerText;
    sf::Text mineCounterText;

    sf::Clock gameClock;
    bool timerStarted;
    bool isDebugMode;
    bool isPaused;

    std::string player;

    int rows;
    int cols;
    int width;
    int height;

    void LoadTextures();
    void SetupUI();
    void HandleMouseClick(sf::Event::MouseButtonEvent mouse);
    void Draw();

public:
    GameWindow(int width, int height, int rows, int cols, int mines, const std::string& playerName);
    void run();
};
