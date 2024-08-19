#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "piece.h"
class Board {
    public:
        Board(int width, int height);

        ~Board();

        void render(sf::RenderWindow &window);
        void setCell(int x, int y, int value);
        bool canPlacePiece(const Piece& piece) const;
        void placePiece(const Piece& piece);
        void clearPiece(const Piece& piece);
        
    private:
        int width;
        int height;
        int cellSize = 40;
        std::vector<std::vector<int>> board;
};

#endif 