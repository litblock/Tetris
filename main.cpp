#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
const int gridWidth = 10;
const int gridHeight = 20;

std::vector<std::vector<std::vector<int>>> tetrisShapes = {
    {{1, 1, 1, 1}}, // I 
    {{2, 2, 2}, {0, 2, 0}}, // T 
    {{3, 3, 0}, {0, 3, 3}}, // Z 
    {{0, 4, 4}, {4, 4, 0}}, // S 
    {{5, 5}, {5, 5}}, // O 
    {{6, 6, 6}, {6, 0, 0}}, // L 
    {{7, 7, 7}, {0, 0, 7}} // J 
};

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris");
    window.setPosition(sf::Vector2i(400, 0));

    Board board(gridWidth, gridHeight);
    Piece piece(tetrisShapes[0]); 
    piece.setPosition(3, 0); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        board.placePiece(piece);
        window.clear();
        board.render(window);
        window.display();
        
    }

    return 0;
}