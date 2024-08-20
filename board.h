#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "piece.h"
#include <queue>
class Board {
    public:
        Board(int width, int height);

        ~Board();

        void render(sf::RenderWindow &window, const Piece& piece, const std::queue<Piece>& upcomingPieces);
        void setCell(int x, int y, int value);
        bool canPlacePiece(const Piece& piece) const;
        void placePiece(const Piece& piece) const;
        void clearPiece(const Piece& piece) const;
        int checkLines();
        Piece getGhostPiece(const Piece& piece) const;
        void renderGameOver(sf::RenderWindow& window);
        void moveFloatingPiecesDown();
        void findConnectedBlocks(int x, int y, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& connectedBlocks);
        int calculateDropDistance(const std::vector<std::pair<int, int>>& piece);
        
    private:
        int width;
        int height;
        int cellSize = 40;
        std::vector<std::vector<int>> board;
        void renderUpcomingPieces(sf::RenderWindow& window, const std::queue<Piece>& upcomingPieces);
};

#endif 