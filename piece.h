#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece {
    public:
        Piece(const std::vector<std::vector<int>>& shape);
        void rotate();
        const std::vector<std::vector<int>>& getShape() const;
        void setPosition(int x, int y);
        int getX() const;
        int getY() const;

    private:
        std::vector<std::vector<std::vector<int>>> shapes;
        int currentRotation;
        int x, y;
    };

#endif