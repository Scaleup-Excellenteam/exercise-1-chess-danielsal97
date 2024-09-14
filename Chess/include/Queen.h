
#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>

class Queen : public Piece {

public:
    explicit Queen(char a) : Piece(a, 9) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);


};
#endif 
