// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
    bool firstMove;

public:
    explicit Rook(char a) : Piece(a, 5) {
        firstMove = true;
    };
/// <summary>
/// check if move is valid for this piece;
/// </summary>
/// <param name="board"></param>
/// <param name="from"></param>
/// <param name="to"></param>
/// <returns></returns>
    int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to);
    const  bool is_firstmove() {
        return firstMove;
    }
};
#endif // ROOK_H
