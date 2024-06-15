#include "Knight.h"

int Knight::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    int x = abs(from[0] - to[0]);
    int y = abs(from[1] - to[1]);
    if ((x == 1 and y == 2) or (x == 2 and y == 1)) {
        return 42;
    }
    return 21;
}