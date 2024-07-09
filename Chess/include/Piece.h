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
protected:
	Piece(const char& name):Pname(name){
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

    const bool getColor() {
        return is_white_color;
    }
};
#endif