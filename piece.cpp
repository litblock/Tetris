#include "piece.h"
#include <cstddef>

Piece::Piece(const std::vector<std::vector<int>>& shape)
    : shapes({shape}), currentRotation(0), x(0), y(0) {
}

void Piece::rotate() {
    std::vector<std::vector<int>> rotated(shapes[currentRotation][0].size(), std::vector<int>(shapes[currentRotation].size()));
    for (std::size_t i = 0; i < shapes[currentRotation].size(); ++i) {
        for (std::size_t j = 0; j < shapes[currentRotation][i].size(); ++j) {
            rotated[j][shapes[currentRotation].size() - 1 - i] = shapes[currentRotation][i][j];
        }
    }
    shapes.push_back(rotated);
    currentRotation = shapes.size() - 1;
}

const std::vector<std::vector<int>>& Piece::getShape() const {
    return shapes[currentRotation];
}

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Piece::move(int dx, int dy) {
    x += dx;
    y += dy;
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}