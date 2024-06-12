#include "Board.h"




int Board::move_piece(const std::string& from, const std::string& to, bool is_white_turn) {
    if (BoardGame[from] == nullptr) return 11;
    if (BoardGame[from]->getColor() != is_white_turn) return 12;
    if (BoardGame[to] != nullptr && BoardGame[from]->getColor() == BoardGame[to]->getColor()) return 13;

    int res = BoardGame[from]->valid_movment(BoardGame, from, to);
    if (res == 42) {
        if (BoardGame[from]->Pname == 'K')
            white_king_location = to;
        else if (BoardGame[from]->Pname == 'k')
            black_king_location = to;

        BoardGame[to] = BoardGame[from];
        BoardGame[from] = nullptr;
        turn = !turn;
        if (BoardGame[to]->getColor()) {
            res = BoardGame[to]->check_cause_check(BoardGame, white_king_location);
            if (res == 31) {
                BoardGame[from] = BoardGame[to];
                BoardGame[to] = nullptr;
                turn = !turn;
                return 31;
            }
            res = BoardGame[to]->checkForCheck(BoardGame, to, black_king_location);
            if (res == 41) return 41;

        }
        else
            res = BoardGame[to]->check_cause_check(BoardGame, black_king_location);
            if (res == 31) {
                BoardGame[from] = BoardGame[to];
                BoardGame[to] = nullptr;
                turn = !turn;
                return 31;
            }
            res = BoardGame[to]->checkForCheck(BoardGame, to, white_king_location);
            if (res == 41) return 41;
    }


    return res;
}

bool Board::getTurn() {
    return turn;
}
