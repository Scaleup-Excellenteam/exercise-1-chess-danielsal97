#include "Queen.h"
#include <cmath>  // Include for std::abs

bool isPathClear(const std::map<std::string, std::shared_ptr<Piece>>& board, std::string from, std::string to) {
    int dx = (to[0] > from[0]) ? 1 : (to[0] < from[0] ? -1 : 0);
    int dy = (to[1] > from[1]) ? 1 : (to[1] < from[1] ? -1 : 0);

    char x = from[0] + dx;
    char y = from[1] + dy;

    while (x != to[0] || y != to[1]) {
        std::string pos = std::string(1, x) + std::string(1, y);
        if (board.find(pos) != board.end() && board.at(pos) != nullptr) {
            return false; 
        }
        x += dx;
        y += dy;
    }
    return true;
}

int Queen::valid_movment (const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    if (from[0] == to[0] || from[1] == to[1] || abs(from[0] - to[0]) == abs(from[1] - to[1])) {
        if (isPathClear(board, from, to)) {
            return 42; 
        }
        else {
            return 21; 
        }
    }
    return 21; 
}
