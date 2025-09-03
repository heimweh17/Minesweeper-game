#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
private:
    sf::Sprite hiddenSprite;
    sf::Sprite revealedSprite;
    sf::Sprite flagSprite;
    sf::Sprite mineSprite;
    sf::Sprite numberSprite;

    sf::Vector2f position;

    bool hasMine = false;
    bool isFlagged = false;
    bool isRevealed = false;
    int adjacentMines = 0;

    std::vector<Tile*> neighbors;

public:
    Tile();
    int GetAdjacentMines() const;

    void SetPosition(float x, float y);
    void SetMine(bool value);
    void ToggleFlag();
    void Reveal();
    void SetNumber(int count);
    void SetNeighbors(const std::vector<Tile*>& neighbors);

    bool Contains(sf::Vector2f mousePos) const;
    bool IsRevealed() const;
    bool IsFlagged() const;
    bool HasMine() const;

    void Draw(sf::RenderWindow& window, bool debugMode = false) const;

    std::vector<Tile*> GetNeighbors() const;
};
