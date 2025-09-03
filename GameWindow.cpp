#include "GameWindow.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor
GameWindow::GameWindow(int w, int h, int r, int c, int mines, const std::string& playerName)
        : window(sf::VideoMode(w, h), "Minesweeper"),
          board(r, c, mines),
          player(playerName),
          rows(r), cols(c),
          width(w), height(h),
          timerStarted(false),
          isDebugMode(false),
          isPaused(false) {
    font.loadFromFile("files/font.ttf");

    mineCounterText.setFont(font);
    mineCounterText.setCharacterSize(24);
    mineCounterText.setFillColor(sf::Color::Red);
    mineCounterText.setPosition(16, height - 50);  // Adjust position as needed

    // Initial value
    int remaining = board.GetTotalMines() - board.GetFlagsPlaced();
    mineCounterText.setString(std::to_string(remaining));

    LoadTextures();
    SetupUI();
    gameClock.restart();
}

// Load UI textures
void GameWindow::LoadTextures() {
    std::vector<std::string> names = {
            "debug", "pause", "play", "face_happy", "face_lose", "face_win", "leaderboard"
    };

    for (const auto& name : names) {
        sf::Texture texture;
        if (!texture.loadFromFile("files/images/" + name + ".png")) {
            throw std::runtime_error("Failed to load: " + name + ".png");
        }
        textureMap[name] = texture;
    }
}


// Setup UI elements
void GameWindow::SetupUI() {
    // Button positions
    buttons["face_happy"].setTexture(textureMap["face_happy"]);
    buttons["face_happy"].setPosition((width / 2) - 32, rows * 32);

    buttons["debug"].setTexture(textureMap["debug"]);
    buttons["debug"].setPosition((cols * 32) - 304, rows * 32);

    buttons["pause"].setTexture(textureMap["pause"]);
    buttons["pause"].setPosition((cols * 32) - 240, rows * 32);

    buttons["leaderboard"].setTexture(textureMap["leaderboard"]);
    buttons["leaderboard"].setPosition((cols * 32) - 176, rows * 32);

    if (!font.loadFromFile("files/font.ttf")) {
        throw std::runtime_error("Font not found");
    }

    mineCounterText.setFont(font);
    mineCounterText.setCharacterSize(24);


    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setPosition((cols * 32) - 100, rows * 32 + 10);
}



// Handle all mouse input
void GameWindow::HandleMouseClick(sf::Event::MouseButtonEvent mouse) {
    sf::Vector2f mousePos(mouse.x, mouse.y);

    if (buttons["face_happy"].getGlobalBounds().contains(mousePos)) {
        board.Reset();
        gameClock.restart();
        timerStarted = false;
        return;
    }

    if (buttons["debug"].getGlobalBounds().contains(mousePos)) {
        isDebugMode = !isDebugMode;
        return;
    }

    if (buttons["pause"].getGlobalBounds().contains(mousePos)) {
        isPaused = !isPaused;
        buttons["pause"].setTexture(textureMap[isPaused ? "play" : "pause"]);
        return;
    }

    if (buttons["leaderboard"].getGlobalBounds().contains(mousePos)) {
        // TODO: Show leaderboard window
        return;
    }

    if (!isPaused && !board.IsGameOver()) {
        if (mouse.button == sf::Mouse::Left) {
            board.HandleLeftClick(mouse.x, mouse.y);
            timerStarted = true;
        } else if (mouse.button == sf::Mouse::Right) {
            board.HandleRightClick(mouse.x, mouse.y);
        }
    }
}


// Drawing the window
void GameWindow::Draw() {
    window.clear(sf::Color::White);
    board.Draw(window, isDebugMode);

    for (const auto& [name, sprite] : buttons) {
        window.draw(sprite);
    }

    mineCounterText.setString("Mines: " + std::to_string(board.getRemainingMines()));

    if (timerStarted) {
        int seconds = static_cast<int>(gameClock.getElapsedTime().asSeconds());
        timerText.setString("Time: " + std::to_string(seconds));
    }

    window.draw(mineCounterText);
    window.draw(timerText);

    window.display();
}

// Main loop
void GameWindow::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                HandleMouseClick(event.mouseButton);
            }
        }

        Draw();
    }
}
