#include "board.h"

Board::Board(int width, int height) : width(width), height(height) {
    board.resize(height, std::vector<int>(width, 0));
}

Board::~Board() {
    
}

void Board::render(sf::RenderWindow& window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setFillColor(sf::Color::White);
            cell.setPosition(i * cellSize, j * cellSize);
            window.draw(cell);
        }
    }
}

void Board::setCell(int x, int y, int value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        board[y][x] = value;
    }
}