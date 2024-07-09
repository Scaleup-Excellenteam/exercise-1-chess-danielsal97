#include "King.h"

int King::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    int row_diff = abs(from[0] - to[0]);
    int col_diff = abs(from[1] - to[1]);
    if (row_diff > 1 or col_diff > 1) return 21;
    has_moved = true;
    return 42;
}