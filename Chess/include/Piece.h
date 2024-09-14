#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <memory>
#include <map>
#include <iostream>
using namespace std;
class Piece {
public:
	virtual ~Piece() = default;
	char Pname;
    bool is_white_color;
    int score;
    enum  MoveResult {
        NoPieceAtSource = 11,
        NotYourTurn = 12,
        InvalidDestination = 13,
        InvalidMovement = 21,
        ImmediateCheck = 31,
        CheckToOpponent = 41,
        validMovement = 42,
        valid_casteling = 43,
        Checkmate = 44
    };
protected:
	Piece(const char& name, const int points):Pname(name), score(points){
        if (isupper(name)) is_white_color = 1;
        else is_white_color = 0;
    }
public:
    bool has_moved = false;
    bool has_checked = false;
	Piece() = default;
    Piece& operator=(const Piece& other) {
        // Handle self-assignment
        if (this != &other) {
            // Copy members from other to this
        }
        return *this;
    }
    virtual int valid_movment(const map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to)  = 0;
    void set_has_checked() {
        has_checked = true;
    }
    const bool getColor() {
        return is_white_color;
    }

    friend std::ostream& operator<<(std::ostream& os, const Piece& piece) {
        os << piece.Pname << " (Score: " << piece.score << ")";
        return os;
    }

};
#endif