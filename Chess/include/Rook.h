// Rook.h
#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {
public:
    explicit Rook(char a) : Piece(a) {};
/// <summary>
/// check if move is valid for this piece;
/// </summary>
/// <param name="board"></param>
/// <param name="from"></param>
/// <param name="to"></param>
/// <returns></returns>
int valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) const{
    
    if (from[0] == to[0]) {
        char start = min(from[1], to[1]);
        char end = max(from[1], to[1]);

        for (char i = start + 1; i < end; ++i) {
            string pos = from[0] + string(1, i);
            auto it = board.find(pos);
            if (it->second != nullptr) {
                return 21;
            }
        }
        return 42;
       
    }
    else if (from[1] == to[1]) {
        char start = min(from[0], to[0]);
        char end = max(from[0], to[0]);
        char king_check;
        if (board.find(from)->second->getColor())
            king_check = 'k';
        else
            king_check = 'K';

        for (char i = start + 1; i < end; ++i) {

            string pos = string(1, i) + to[1];

            auto it = board.find(pos);
 
          
            if (it->second != nullptr) {
                return 21;
            }
        }
    
        return 42;
    }
    else  return 21;

}
/// <summary>
/// checks if the move can cause for self check
/// </summary>
/// <param name="board"></param>
/// <param name="king_location"></param>
/// <returns></returns>
int check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location)const {

    char row = king_location[0];
    char col = king_location[1];
    for (char i = row ; i <= 'h'; ++i) {
        string pos = string(1,row) + king_location[1];
        auto it = board.find(pos);
        if (it->second != nullptr and it->second->getColor() != board.find(king_location)->second->getColor())
            return 31;
        else if (it->second != nullptr and it->second->Pname != board.find(king_location)->second->Pname)
            return 42;
    }
    for (char i = row ; i <= 'a'; --i) {
        string pos = string(1, row) + king_location[1];
        auto it = board.find(pos);
        if (it->second != nullptr and it->second->getColor() != board.find(king_location)->second->getColor())
            return 31;
        else if (it->second != nullptr and it->second->Pname == board.find(king_location)->second->Pname)
            return 42;
    }
    for (char i = col ; i <= '8'; ++i) {
        string pos = king_location[0] + string(1, col);
        auto it = board.find(pos);
    //    if (it->second != nullptr) {
     //       cout << it->second->Pname << " king location: " << board.find(king_location)->second->Pname;
       //     cin >> start_row;
       // }
        if (it->second != nullptr and it->second->getColor() != board.find(king_location)->second->getColor())
            return 31;
        else if (it->second != nullptr and it->second->Pname == board.find(king_location)->second->Pname)
            return 42;
    }
    for (char i = col; i <= '1'; --i) {
        string pos = king_location[0] + string(1, col);
        auto it = board.find(pos);
        if (it->second != nullptr and it->second->getColor() != board.find(king_location)->second->getColor())
            return 31;
        else if (it->second != nullptr and it->second->Pname == board.find(king_location)->second->Pname)
            return 42;
    }

    return 41;
}

/// <summary>
/// checks if the move will cause check to opponent
/// </summary>
/// <param name="board"></param>
/// <param name="piece_location"></param>
/// <param name="king_location"></param>
/// <returns></returns>
int checkForCheck(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& piece_location, const std::string& king_location) const {
    char start = min(piece_location[0], king_location[0]);
    char end = max(piece_location[0], king_location[0]);
    for (char i = start; i < end ; ++i) {
        string pos = string(1, i) + king_location[1];
        auto it = board.find(pos);
        if (it->second != nullptr) {
            return check_cause_check(board, king_location);
        }

    } 
    for (char i = end; i < start ; --i) {
        string pos = string(1, i) + king_location[1];
        auto it = board.find(pos);
        if (it->second != nullptr) {
            return check_cause_check(board, king_location);
        }

    }

    start = min(piece_location[1], king_location[1]);
    end = max(piece_location[1], king_location[1]);
    for (char i = start; i < end ; ++i) {
        string pos = king_location[0] + string(1, i);
        auto it = board.find(pos);
        if (it->second != nullptr) {
            return check_cause_check(board, king_location);
        }
    }
    for (char i = end; i < start ; --i) {
        string pos = king_location[0] + string(1, i);
        auto it = board.find(pos);
        if (it->second != nullptr) {
            return check_cause_check(board, king_location);
        }
    }
    return 42;
}


};
#endif // ROOK_H
