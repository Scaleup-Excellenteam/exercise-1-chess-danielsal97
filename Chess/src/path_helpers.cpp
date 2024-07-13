#include "path_helpers.h"

bool isPathClearVerticalHorizontal(const std::map<std::string, std::shared_ptr<Piece>>& board, char fixed, char start, char end, bool isVertical) {
    for (char i = start + 1; i < end; ++i) {
        std::string pos = isVertical ? std::string(1, fixed) + std::string(1, i) : std::string(1, i) + std::string(1, fixed);
        if (board.at(pos) != nullptr) {
            return false; // Path is blocked
        }
    }
    return true; // Path is clear
}

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
