#include "Rook.h"

int Rook::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {

    if (from[0] == to[0]) {
        char start = min(from[1], to[1]);
        char end = max(from[1], to[1]);

        for (char i = start + 1; i < end; ++i) {
            string pos = from[0] + string(1, i);
            auto it = board.find(pos);
            if (it->second != nullptr) {
                return 21;
            }
        }
        return 42;

    }
    else if (from[1] == to[1]) {
        char start = min(from[0], to[0]);
        char end = max(from[0], to[0]);
        char king_check;
        if (board.find(from)->second->getColor())
            king_check = 'k';
        else
            king_check = 'K';

        for (char i = start + 1; i < end; ++i) {

            string pos = string(1, i) + to[1];

            auto it = board.find(pos);


            if (it->second != nullptr) {
                return 21;
            }
        }

        return 42;
    }
    else  return 21;

}