// Rook.h
#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {

public:
    explicit King(char a) : Piece(a) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);
};
#endif // ROOK_H
