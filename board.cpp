#include "board.h"
#include <iostream>

Board::Board(int width, int height) : width(width), height(height) {
    board.resize(height, std::vector<int>(width, 0));
}

Board::~Board() {
    
}

void Board::render(sf::RenderWindow& window, const Piece& currentPiece, const std::queue<Piece>& upcomingPieces) {
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

    Piece ghostPiece = getGhostPiece(currentPiece);
    const auto& ghostShape = ghostPiece.getShape();
    int ghostX = ghostPiece.getX();
    int ghostY = ghostPiece.getY();

    for (int i = 0; i < static_cast<int>(ghostShape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(ghostShape[i].size()); ++j) {
            if (ghostShape[i][j] != 0) {
                sf::RectangleShape ghostCell(sf::Vector2f(cellSize - 1, cellSize - 1));
                ghostCell.setFillColor(sf::Color(128, 128, 128, 100));
                ghostCell.setOutlineColor(sf::Color(255, 255, 255, 200)); 
                ghostCell.setOutlineThickness(2);
                ghostCell.setPosition((ghostX + j) * cellSize, (ghostY + i) * cellSize);
                window.draw(ghostCell);
            }
        }
    }

    const auto& currentShape = currentPiece.getShape();
    int currentX = currentPiece.getX();
    int currentY = currentPiece.getY();

    for (int i = 0; i < static_cast<int>(currentShape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(currentShape[i].size()); ++j) {
            if (currentShape[i][j] != 0) {
                sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                switch (currentShape[i][j]) {
                    case 1: cell.setFillColor(sf::Color::Cyan); break;
                    case 2: cell.setFillColor(sf::Color::Magenta); break;
                    case 3: cell.setFillColor(sf::Color::Red); break;
                    case 4: cell.setFillColor(sf::Color::Green); break;
                    case 5: cell.setFillColor(sf::Color::Yellow); break;
                    case 6: cell.setFillColor(sf::Color::Blue); break;
                    case 7: cell.setFillColor(sf::Color(255, 165, 0)); break;
                    default: cell.setFillColor(sf::Color::White); break;
                }
                cell.setPosition((currentX + j) * cellSize, (currentY + i) * cellSize);
                window.draw(cell);
            }
        }
    }

    renderUpcomingPieces(window, upcomingPieces);
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

    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(shape[i].size()); ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                
                if (boardX < 0 || boardX >= width || boardY >= height) {
                    return false;
                }
                
            
                if (boardY >= 0 && board[boardY][boardX] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::placePiece(const Piece& piece) const {
    const auto& shape = piece.getShape();
    int x = piece.getX();
    int y = piece.getY();

    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(shape[i].size()); ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                if (boardX >= 0 && boardX < width && boardY >= 0 && boardY < height) {
                    const_cast<Board*>(this)->board[boardY][boardX] = shape[i][j];
                }
            }
        }
    }
}

void Board::clearPiece(const Piece& piece) const {
    const auto& shape = piece.getShape();
    int x = piece.getX();
    int y = piece.getY();

    for (int i = 0; i < static_cast<int>(shape.size()); ++i) {
        for (int j = 0; j < static_cast<int>(shape[i].size()); ++j) {
            if (shape[i][j] != 0) {
                int boardX = x + j;
                int boardY = y + i;
                if (boardX >= 0 && boardX < width && boardY >= 0 && boardY < height) {
                    const_cast<Board*>(this)->board[boardY][boardX] = 0;
                }
            }
        }
    }
}

int Board::checkLines() {
    int linesCleared = 0;

    for (int y = height - 1; y >= 0; --y) {
        bool fullLine = true;


        for (int x = 0; x < width; ++x) {
            if (board[y][x] == 0) {
                fullLine = false;
                break;
            }
        }

        if (fullLine) {
            linesCleared++;
            for (int x = 0; x < width; ++x) {
                board[y][x] = 0;
            }
        }
    }

    return linesCleared;
}

Piece Board::getGhostPiece(const Piece& piece) const {
    Piece ghostPiece = piece;
    int moveCount = 0;
    
    //std::cout << "Original piece position: (" << piece.getX() << ", " << piece.getY() << ")" << std::endl;

    clearPiece(piece);
    
    while (canPlacePiece(ghostPiece)) {
        ghostPiece.move(0, 1);
        moveCount++;
    }
    
    if (moveCount > 0) {
        ghostPiece.move(0, -1);  
        moveCount--;
    }
    
    placePiece(piece);
    
    //std::cout << "Ghost piece moved down " << moveCount << " rows" << std::endl;
    //std::cout << "Final ghost piece position: (" << ghostPiece.getX() << ", " << ghostPiece.getY() << ")" << std::endl;
    
    return ghostPiece;
}

void Board::renderUpcomingPieces(sf::RenderWindow& window, const std::queue<Piece>& upcomingPieces) {
    std::queue<Piece> tempQueue = upcomingPieces; 
    int yOffset = 50;

    for (int i = 0; i < 3 && !tempQueue.empty(); ++i) { 
        Piece nextPiece = tempQueue.front();
        tempQueue.pop();

        int previewX = (width + 2) * cellSize;
        int previewY = yOffset + i * 4 * cellSize;

        const auto& shape = nextPiece.getShape();
        for (size_t y = 0; y < shape.size(); ++y) {
            for (size_t x = 0; x < shape[y].size(); ++x) {
                if (shape[y][x] != 0) {
                    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                    switch (shape[y][x]) {
                        case 1: cell.setFillColor(sf::Color::Cyan); break;
                        case 2: cell.setFillColor(sf::Color::Magenta); break;
                        case 3: cell.setFillColor(sf::Color::Red); break;
                        case 4: cell.setFillColor(sf::Color::Green); break;
                        case 5: cell.setFillColor(sf::Color::Yellow); break;
                        case 6: cell.setFillColor(sf::Color::Blue); break;
                        case 7: cell.setFillColor(sf::Color(255, 165, 0)); break;
                    }
                    cell.setPosition(previewX + x * cellSize, previewY + y * cellSize);
                    window.draw(cell);
                }
            }
        }
    }
}

void Board::renderGameOver(sf::RenderWindow& window) {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            switch (board[j][i]) {
                case 1: cell.setFillColor(sf::Color(0, 255, 255, 128)); break; 
                case 2: cell.setFillColor(sf::Color(255, 0, 255, 128)); break; 
                case 3: cell.setFillColor(sf::Color(255, 0, 0, 128)); break; 
                case 4: cell.setFillColor(sf::Color(0, 255, 0, 128)); break; 
                case 5: cell.setFillColor(sf::Color(255, 255, 0, 128)); break; 
                case 6: cell.setFillColor(sf::Color(0, 0, 255, 128)); break; 
                case 7: cell.setFillColor(sf::Color(255, 165, 0, 128)); break; 
                default: cell.setFillColor(sf::Color(255, 255, 255, 32)); break; 
            }
            cell.setPosition(i * cellSize, j * cellSize);
            window.draw(cell);
        }
    }
}

void Board::moveFloatingPiecesDown() {
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            if (board[y][x] != 0 && !visited[y][x]) {
                std::vector<std::pair<int, int>> piece;
                findConnectedBlocks(x, y, visited, piece);

                int dropDistance = calculateDropDistance(piece);

                for (const auto& block : piece) {
                    board[block.second + dropDistance][block.first] = board[block.second][block.first];
                    board[block.second][block.first] = 0;
                }
            }
        }
    }
}

void Board::findConnectedBlocks(int x, int y, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& piece) {
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    visited[y][x] = true;

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();
        piece.push_back({cx, cy});

        for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int nx = cx + dx;
            int ny = cy + dy;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx] != 0 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
}

int Board::calculateDropDistance(const std::vector<std::pair<int, int>>& piece) {
    int dropDistance = height;

    for (const auto& block : piece) {
        int x = block.first;
        int y = block.second;

        int distance = 0;
        while (y + distance + 1 < height && board[y + distance + 1][x] == 0) {
            distance++;
        }

        dropDistance = std::min(dropDistance, distance);
    }

    return dropDistance;
}