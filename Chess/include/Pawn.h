
#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <string>

class Pawn : public Piece {

public:
    int first_move = 1;
    explicit Pawn(char a) : Piece(a,1) {};
    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);

};
#endif 
