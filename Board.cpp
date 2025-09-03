#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board(int r, int c, int mines)
        : rows(r), cols(c), totalMines(mines), gameOver(false), gameWon(false) {

    std::srand(static_cast<unsigned int>(time(nullptr)));

    // Step 1: Initialize the grid
    tileGrid.resize(rows, std::vector<Tile>(cols));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            tileGrid[row][col].SetPosition(static_cast<float>(col * 32), static_cast<float>(row * 32));
        }
    }

    // Step 2–4
    PlaceMines();
    SetNeighbors();
    CountAdjacentMines();
}

void Board::PlaceMines() {
    int placed = 0;
    while (placed < totalMines) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (!tileGrid[r][c].HasMine()) {
            tileGrid[r][c].SetMine(true);
            ++placed;
        }
    }
}

void Board::SetNeighbors() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::vector<Tile*> neighbors;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;

                    int nr = row + dr;
                    int nc = col + dc;

                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                        neighbors.push_back(&tileGrid[nr][nc]);
                    }
                }
            }
            tileGrid[row][col].SetNeighbors(neighbors);
        }
    }
}

void Board::CountAdjacentMines() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int count = 0;
            for (Tile* neighbor : tileGrid[row][col].GetNeighbors()) {
                if (neighbor->HasMine()) ++count;
            }
            tileGrid[row][col].SetNumber(count);
        }
    }
}
void Board::FloodReveal(Tile& tile) {
    if (tile.IsRevealed() || tile.IsFlagged() || tile.HasMine()) return;

    tile.Reveal();

    if (tile.GetAdjacentMines() == 0) {
        for (Tile* neighbor : tile.GetNeighbors()) {
            if (!neighbor->IsRevealed()) {
                FloodReveal(*neighbor);
            }
        }
    }
}

void Board::Draw(sf::RenderWindow& window, bool debugMode) {
    for (const auto& row : tileGrid) {
        for (const Tile& tile : row) {
            tile.Draw(window, debugMode);
        }
    }
}

void Board::HandleLeftClick(int x, int y) {
    if (gameOver) return;

    int col = x / 32;
    int row = y / 32;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        Tile& tile = tileGrid[row][col];

        if (!tile.IsRevealed() && !tile.IsFlagged()) {
            FloodReveal(tile);
            if (CheckWinCondition()) {
                gameWon = true;
                // optionally: reveal all mines or trigger win UI
            }
            if (tile.HasMine()) {
                gameOver = true;
                // Optionally reveal all mines
            }
        }
    }
}

void Board::HandleRightClick(int x, int y) {
    if (gameOver) return;

    int col = x / 32;
    int row = y / 32;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        Tile& tile = tileGrid[row][col];


    }
}

void Board::Reset() {
    tileGrid.clear();
    gameOver = false;

    tileGrid.resize(rows, std::vector<Tile>(cols));
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            tileGrid[row][col].SetPosition(static_cast<float>(col * 32), static_cast<float>(row * 32));
        }
    }

    PlaceMines();
    SetNeighbors();
    CountAdjacentMines();
}
bool Board::CheckWinCondition() const {
    for (const auto& row : tileGrid) {
        for (const auto& tile : row) {
            if (!tile.HasMine() && !tile.IsRevealed()) {
                return false;
            }
        }
    }
    return true;
}
bool Board::IsGameOver() const {
    return gameOver;
}

int Board::getRemainingMines() {
    int flagsPlaced = 0;
    for (const auto& row : tileGrid) {
        for (const auto& tile : row) {
            if (tile.IsFlagged()) {
                flagsPlaced++;
            }
        }
    }
    return totalMines - flagsPlaced;
}

