
#ifndef KNIHGT_H
#define kNIGHT_H

#include "Piece.h"
#include <string>

class Knight : public Piece {

public:
    explicit Knight(char a) : Piece(a,3) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);
};
#endif 
