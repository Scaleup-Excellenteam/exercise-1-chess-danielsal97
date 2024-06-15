#include "Pawn.h"
int Pawn::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    if (board.find(from)->second->Pname == 'p') {
        if (board.find(to)->second == nullptr) {
            if (first_move == 1) {

                if (from[0] - to[0] <= 2 and from[0] - to[0] > 0 and from[1] == to[1]) {
                    if (from[0] - to[0] == 2 and board.find(string(1, from[0] + 1) + to[1])->second != nullptr) {
                        return 21;
                     }
                    first_move = 0;
                    return 42;
                }
            }
            else if (from[0] - to[0] == 1 and from[1] == to[1]) {
                first_move = 0;
                return 42;
            }

        }
        else if (board.find(to)->second != nullptr) {
            if (from[0] - to[0] == 1 and abs(from[1] - to[1]) == 1) {
                first_move = 0;
                return 42;
            }
        }
    }
    else if (board.find(from)->second->Pname == 'P') {
        if (board.find(to)->second == nullptr) {
            if (first_move == 1) {
                if (to[0] - from[0] <= 2 and to[0] - from[0] > 0 and from[1] == to[1]) {
                    first_move = 0;
                    return 42;
                }
            }
            else if (to[0] - from[0] == 1 and from[1] == to[1]) {
                first_move = 0;
                return 42;
            }

        }
        else if (board.find(to)->second != nullptr) {
            if (to[0] - from[0] == 1 and abs(from[1] - to[1]) == 1) {
                first_move = 0;
                return 42;
            }
        }
    }
    return 21;
}
