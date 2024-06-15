
#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include <string>

class Bishop : public Piece {

public:
    explicit Bishop(char a) : Piece(a) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);
    
};
#endif 
