#include "Pawn.h"
#include <cmath> // For std::abs

int Pawn::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    int moveDirection = (board.find(from)->second->Pname == 'P') ? 1 : -1;

    int verticalMove = (to[0] - from[0]) * moveDirection;
    int horizontalMove = std::abs(to[1] - from[1]);

    if (board.find(to)->second == nullptr) {
        if (verticalMove == 1 && horizontalMove == 0) {
            first_move = 0;
            return 42;
        }
        if (first_move && verticalMove == 2 && horizontalMove == 0) {
            std::string between = std::string(1, from[0] + moveDirection) + from[1];
            if (board.find(between)->second != nullptr) return 21;
            first_move = 0;
            return 42;
        }
    }

    if (board.find(to)->second != nullptr && verticalMove == 1 && horizontalMove == 1) {
        first_move = 0;
        return 42;
    }

    return 21; 
}
