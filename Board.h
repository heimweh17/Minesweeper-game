#pragma once
#include <vector>
#include "Tile.h"
#include <SFML/Graphics.hpp>

class Board {
private:
    int rows;
    int cols;
    int totalMines;
    bool gameOver;
    bool gameWon;
    int flagsPlaced;

    std::vector<std::vector<Tile>> tileGrid;

    void PlaceMines();
    void SetNeighbors();
    void CountAdjacentMines();
    void FloodReveal(Tile& tile);

public:
    Board(int r, int c, int mines);

    int getRemainingMines();
    void Draw(sf::RenderWindow& window, bool debugMode);
    void HandleLeftClick(int x, int y);
    void HandleRightClick(int x, int y);
    void Reset();
    bool CheckWinCondition() const;
    bool IsGameOver() const;

    int GetTotalMines() const { return totalMines; }
    int GetFlagsPlaced() const { return flagsPlaced; }
    void IncrementFlags() { ++flagsPlaced; }
    void DecrementFlags() { --flagsPlaced; }
};
