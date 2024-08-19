#include <SFML/Graphics.hpp>
#include <iostream>
#include "board.h"
#include <random>

const int gridWidth = 10;
const int gridHeight = 20;

enum class GameState {
    Playing,
    GameOver
};

std::vector<std::vector<std::vector<int>>> tetrisShapes = {
    {{1, 1, 1, 1}}, // I 
    {{2, 2, 2}, {0, 2, 0}}, // T 
    {{3, 3, 0}, {0, 3, 3}}, // Z 
    {{0, 4, 4}, {4, 4, 0}}, // S 
    {{5, 5}, {5, 5}}, // O 
    {{6, 6, 6}, {6, 0, 0}}, // L 
    {{7, 7, 7}, {0, 0, 7}} // J 
};

Piece getRandomPiece() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tetrisShapes.size() - 1);
    return Piece(tetrisShapes[dis(gen)]);
}

int main(int argc, char const *argv[]) {
    sf::RenderWindow window(sf::VideoMode(600, 800), "Tetris");
    window.setPosition(sf::Vector2i(400, 0));

    Board board(gridWidth, gridHeight);
    std::queue<Piece> upcomingPieces;
    GameState gameState = GameState::Playing;

    for (int i = 0; i < 4; ++i) {
        upcomingPieces.push(getRandomPiece());
    }

    Piece currentPiece = upcomingPieces.front();
    upcomingPieces.pop();
    currentPiece.setPosition(gridWidth / 2 - 1, 0);

    sf::Clock clock;
    float dropTime = 0.5f;

    sf::Font font;
    if (!font.loadFromFile("JetBrainsMono-Medium.ttf")) { 
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!\nPress R to restart");
    gameOverText.setCharacterSize(30);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(400 - gameOverText.getGlobalBounds().width / 2, 400 - gameOverText.getGlobalBounds().height / 2);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (gameState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    board.clearPiece(currentPiece);  
                    if (event.key.code == sf::Keyboard::Left) {
                        currentPiece.move(-1, 0);
                        if (!board.canPlacePiece(currentPiece)) {
                            currentPiece.move(1, 0); 
                        }
                    } else if (event.key.code == sf::Keyboard::Right) {
                        currentPiece.move(1, 0);
                        if (!board.canPlacePiece(currentPiece)) {
                            currentPiece.move(-1, 0); 
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        currentPiece.move(0, 1);
                        if (!board.canPlacePiece(currentPiece)) {
                            currentPiece.move(0, -1); 
                        }
                    } else if (event.key.code == sf::Keyboard::Up) {
                        currentPiece.rotate();
                        if (!board.canPlacePiece(currentPiece)) {
                            currentPiece.rotate(); 
                            currentPiece.rotate();
                            currentPiece.rotate();
                        }
                    }
                } 
            } else if (gameState == GameState::GameOver) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    board = Board(gridWidth, gridHeight);
                    while (!upcomingPieces.empty()) upcomingPieces.pop();
                    for (int i = 0; i < 4; ++i) {
                        upcomingPieces.push(getRandomPiece());
                    }
                    currentPiece = upcomingPieces.front();
                    upcomingPieces.pop();
                    currentPiece.setPosition(gridWidth / 2 - 1, 0);
                    gameState = GameState::Playing;
                }     
            }
        }

        if (gameState == GameState::Playing) {
            if (clock.getElapsedTime().asSeconds() >= dropTime) {
                board.clearPiece(currentPiece);
                currentPiece.move(0, 1);
                if (!board.canPlacePiece(currentPiece)) {
                    currentPiece.move(0, -1);
                    board.placePiece(currentPiece);
                    board.checkLines();
                    
                    currentPiece = upcomingPieces.front();
                    upcomingPieces.pop();
                    currentPiece.setPosition(gridWidth / 2 - 1, 0);
                    
                    upcomingPieces.push(getRandomPiece());

                    if (!board.canPlacePiece(currentPiece)) {
                        gameState = GameState::GameOver;
                    }
                }
                clock.restart();
            }
        }
        window.clear();
        board.render(window, currentPiece, upcomingPieces);
        window.display(); 
    }

    return 0;
}
