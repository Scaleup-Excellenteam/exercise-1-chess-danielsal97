// Rook.h
#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {
    int checkForCheck(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& piece_location, const std::string& king_location) const { return 42; };
    int check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& king_location) const { return 42; }
public:
    explicit King(char a) : Piece(a) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) const {
        int row_diff = abs(from[0] - to[0]);
        int col_diff = abs(from[1] - to[1]);
        if (row_diff > 1 or col_diff > 1) return 21;
        return 42;
    }
};
#endif // ROOK_H
