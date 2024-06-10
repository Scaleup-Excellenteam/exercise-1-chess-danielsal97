#include "Board.h"




int Board::move_piece(const std::string& from, const std::string& to, bool is_white_turn) {
    if (BoardGame[from] == nullptr) return 11;
    if (BoardGame[from]->getColor() != is_white_turn) return 12;
    if (BoardGame[to] != nullptr && BoardGame[from]->getColor() == BoardGame[to]->getColor()) return 13;

    int res = BoardGame[from]->valid_movment(BoardGame, from, to);
    if (res == 42) {
        BoardGame[to] = BoardGame[from];
        BoardGame[from] = nullptr;
        turn = !turn;
        return 42;
    }

    return res;
}

bool Board::getTurn() {
    return turn;
}
