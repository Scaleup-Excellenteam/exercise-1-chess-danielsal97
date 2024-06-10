// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
public:
   
    explicit Rook(char a) : Piece(a) {};

    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) const override {
        if (from[0] == to[0] or from[1] == to[1]) {
            return 42;
        }
        else { 
            return 21;
        }
    }
};

#endif // ROOK_H
