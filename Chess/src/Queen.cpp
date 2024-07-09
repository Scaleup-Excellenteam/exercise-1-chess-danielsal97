#include "Queen.h"
#include <cmath>

// Function to check if the path is clear for vertical and horizontal moves
bool isPathClearVerticalHorizontal(const std::map<std::string, std::shared_ptr<Piece>>& board, char fixed, char start, char end, bool isVertical) {
    for (char i = start + 1; i < end; ++i) {
        std::string pos = isVertical ? std::string(1, fixed) + std::string(1, i) : std::string(1, i) + std::string(1, fixed);
        if (board.at(pos) != nullptr) {
            return false; // Path is blocked
        }
    }
    return true; // Path is clear
}

// Function to check if the path is clear for diagonal moves
bool isPathClearDiagonal(const std::map<std::string, std::shared_ptr<Piece>>& board, char startX, char startY, char endX, char endY) {
    char xIncrement = startX < endX ? 1 : -1;
    char yIncrement = startY < endY ? 1 : -1;
    char x = startX + xIncrement;
    char y = startY + yIncrement;

    while (x != endX && y != endY) {
        std::string pos = std::string(1, x) + std::string(1, y);
        if (board.at(pos) != nullptr) {
            return false; // Path is blocked
        }
        x += xIncrement;
        y += yIncrement;
    }
    return true; // Path is clear
}

int Queen::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    if (from[0] == to[0]) {
        // Vertical movement
        char start = std::min(from[1], to[1]);
        char end = std::max(from[1], to[1]);
        if (isPathClearVerticalHorizontal(board, from[0], start, end, true)) {
            return 42; // Valid move
        }
    }
    else if (from[1] == to[1]) {
        // Horizontal movement
        char start = std::min(from[0], to[0]);
        char end = std::max(from[0], to[0]);
        if (isPathClearVerticalHorizontal(board, from[1], start, end, false)) {
            return 42; // Valid move
        }
    }
    else if (std::abs(from[0] - to[0]) == std::abs(from[1] - to[1])) {
        // Diagonal movement
        if (isPathClearDiagonal(board, from[0], from[1], to[0], to[1])) {
            return 42; // Valid move
        }
    }

    return 21; // Invalid move or path is blocked
}
