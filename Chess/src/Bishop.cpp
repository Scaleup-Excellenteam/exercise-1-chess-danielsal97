#include "Bishop.h"

int Bishop::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    if (abs(from[0] - to[0]) == abs(from[1] - to[1])) {
        char start_x = min(from[0], to[0]);
        char end_x = max(from[0], to[0]);
        char start_y = min(from[1], to[1]);
        char end_y = max(from[1], to[1]);
        for (char x = start_x + 1, y = start_y + 1; x < end_x && y < end_y; x++, y++) {
            std::string pos = std::string(1, x) + std::string(1, y);

            if (board.find(pos)->second != nullptr) {

                return 21;
            }
        }
        return 42;
    }
    return 21;
}