#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
const int gridWidth = 10;
const int gridHeight = 20;

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris");
    window.setPosition(sf::Vector2i(400, 0));

    Board board(gridWidth, gridHeight);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        board.render(window);
        window.display();
        
    }

    return 0;
}