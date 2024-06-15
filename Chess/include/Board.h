#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
class Board {
    std::map<std::string, std::shared_ptr<Piece>> BoardGame;
    bool turn = true;
    string white_king_location, black_king_location;

public:
    explicit Board(const std::string& start);

    int move_piece(const std::string& from, const std::string& to, bool is_white_turn);
    bool getTurn();
    int check_cause_checkmate(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location);
    int check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location);
};

#endif // BOARD_H
