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
            switch (board[j][i]) {
                case 1: cell.setFillColor(sf::Color::Cyan); break; // I 
                case 2: cell.setFillColor(sf::Color::Magenta); break; // T 
                case 3: cell.setFillColor(sf::Color::Red); break; // Z 
                case 4: cell.setFillColor(sf::Color::Green); break; // S 
                case 5: cell.setFillColor(sf::Color::Yellow); break; // O 
                case 6: cell.setFillColor(sf::Color::Blue); break; // L 
                case 7: cell.setFillColor(sf::Color(255, 165, 0)); break; // J 
                default: cell.setFillColor(sf::Color::White); break; // empty
            }
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

bool Board::canPlacePiece(const Piece& piece) const {
    const auto& shape = piece.getShape();
    int x = piece.getX();
    int y = piece.getY();

    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                if (boardX < 0 || boardX >= width || boardY < 0 || boardY >= height || board[boardY][boardX] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::placePiece(const Piece& piece) {
    const auto& shape = piece.getShape();
    int x = piece.getX();
    int y = piece.getY();

    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(shape[i].size()); ++j) {
            if (shape[i][j] != 0) {
                setCell(x + j, y + i, shape[i][j]);
            }
        }
    }
}

void Board::clearPiece(const Piece& piece) {
    const auto& shape = piece.getShape();
    int x = piece.getX();
    int y = piece.getY();

    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(shape[i].size()); ++j) {
            if (shape[i][j] != 0) {
                setCell(x + j, y + i, 0);
            }
        }
    }
}