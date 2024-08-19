#include "piece.h"

Piece::Piece(const std::vector<std::vector<int>>& shape)
    : shapes({shape}), currentRotation(0), x(0), y(0) {
}

void Piece::rotate() {
    currentRotation = (currentRotation + 1) % shapes.size();
}

const std::vector<std::vector<int>>& Piece::getShape() const {
    return shapes[currentRotation];
}

void Piece::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Piece::getX() const {
    return x;
}

int Piece::getY() const {
    return y;
}