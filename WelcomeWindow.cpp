
#include "WelcomeWindow.h"
#include <iostream>
#include <cctype>

WelcomeWindow::WelcomeWindow(int width, int height) : windowWidth(width), windowHeight(height) {
    if (!font.loadFromFile("files/font.ttf")) {
        throw std::runtime_error("Could not load font.ttf");
    }

    titleText = createCenteredText("WELCOME TO MINESWEEPER!", 24, height / 2 - 150, sf::Color::White, true, true);
    promptText = createCenteredText("Enter your name:", 20, height / 2 - 75, sf::Color::White, true);

    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(sf::Color::Yellow);
    inputText.setPosition(width / 2, height / 2 - 45);
}

sf::Text WelcomeWindow::createCenteredText(const std::string& str, unsigned int size, float y, sf::Color color, bool bold, bool underline) {
    sf::Text text(str, font, size);
    text.setFillColor(color);
    if (bold) text.setStyle(sf::Text::Bold);
    if (underline) text.setStyle(text.getStyle() | sf::Text::Underlined);
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2, bounds.height);
    text.setPosition(windowWidth / 2, y);
    return text;
}

void WelcomeWindow::handleEvent(sf::Event& event, sf::RenderWindow& window, bool& done) {
    if (event.type == sf::Event::Closed) {
        window.close();
        done = true;
    } else if (event.type == sf::Event::TextEntered) {
        char c = static_cast<char>(event.text.unicode);
        if (c == '\b' && !playerName.empty()) {
            playerName.pop_back();
        } else if (std::isalpha(c) && playerName.size() < 10) {
            playerName += std::tolower(c);
        }
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (!playerName.empty()) {
            done = true;
        }
    }
}

void WelcomeWindow::updateInputText() {
    std::string formatted = playerName;
    if (!formatted.empty()) {
        formatted[0] = std::toupper(formatted[0]);
        for (size_t i = 1; i < formatted.size(); ++i)
            formatted[i] = std::tolower(formatted[i]);
    }
    inputText.setString(formatted + "|");
    sf::FloatRect bounds = inputText.getLocalBounds();
    inputText.setOrigin(bounds.width / 2, bounds.height);
}

void WelcomeWindow::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Blue);
    window.draw(titleText);
    window.draw(promptText);
    window.draw(inputText);
    window.display();
}

std::string WelcomeWindow::run() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Welcome to Minesweeper", sf::Style::Close);
    window.setFramerateLimit(60);

    bool done = false;

    while (window.isOpen() && !done) {
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvent(event, window, done);
        }

        updateInputText();
        draw(window);
    }

    return playerName;
}

