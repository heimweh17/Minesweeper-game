#include "Tile.h"
#include "TextureManager.h"

Tile::Tile() {
    hiddenSprite.setTexture(TextureManager::GetTexture("tile_hidden.png"));
    revealedSprite.setTexture(TextureManager::GetTexture("tile_revealed.png"));
    flagSprite.setTexture(TextureManager::GetTexture("flag.png"));
    mineSprite.setTexture(TextureManager::GetTexture("mine.png"));
}

void Tile::SetPosition(float x, float y) {
    position = {x, y};
    hiddenSprite.setPosition(position);
    revealedSprite.setPosition(position);
    flagSprite.setPosition(position);
    mineSprite.setPosition(position);
    numberSprite.setPosition(position);
}

void Tile::SetMine(bool value) {
    hasMine = value;
}

void Tile::ToggleFlag() {
    if (!isRevealed)
        isFlagged = !isFlagged;
}

void Tile::Reveal() {
    if (!isFlagged)
        isRevealed = true;
}

void Tile::SetNumber(int count) {
    adjacentMines = count;
    if (count > 0) {
        numberSprite.setTexture(TextureManager::GetTexture("number_" + std::to_string(count) + ".png"));
    }
}

void Tile::SetNeighbors(const std::vector<Tile*>& neigh) {
    neighbors = neigh;
}

std::vector<Tile*> Tile::GetNeighbors() const {
    return neighbors;
}

bool Tile::Contains(sf::Vector2f mousePos) const {
    return hiddenSprite.getGlobalBounds().contains(mousePos);
}

bool Tile::IsRevealed() const {
    return isRevealed;
}

bool Tile::IsFlagged() const {
    return isFlagged;
}

bool Tile::HasMine() const {
    return hasMine;
}
int Tile::GetAdjacentMines() const {
    return adjacentMines;
}

void Tile::Draw(sf::RenderWindow& window, bool debugMode) const {
    // Always draw base tile (e.g., revealed or hidden)
    if (isRevealed) {
        window.draw(revealedSprite);
        if (hasMine) {
            window.draw(mineSprite);  // or explosionSprite if you want
        } else if (adjacentMines > 0) {
            window.draw(numberSprite);
        }
    } else {
        window.draw(hiddenSprite);
        if (isFlagged) {
            window.draw(flagSprite);
        } else if (debugMode && hasMine) {
            window.draw(mineSprite);
        }
    }
}

