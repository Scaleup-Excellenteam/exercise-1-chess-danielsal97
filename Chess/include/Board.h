#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "Piece.h"
#include "Rook.h"
#include "King.h"

class Board {
    std::map<std::string, std::shared_ptr<Piece>> BoardGame;
    bool turn = true;
    string white_king, black_king;

public:
    explicit Board(const std::string& start) {
        // Initialize the board with empty squares
        for (char row = '1'; row <= '8'; row++) {
            for (char col = 'a'; col <= 'h'; col++) {
                std::string key = std::string(1, col) + row;
                BoardGame[key] = nullptr;
            }
        }

        // Place pieces based on the provided string
        auto mapIt = BoardGame.begin();
        auto strIt = start.begin();
        while (mapIt != BoardGame.end() && strIt != start.end()) {
            if (*strIt == 'R' || *strIt == 'r') {
                std::shared_ptr<Rook> rook = std::make_shared<Rook>(*strIt);
                mapIt->second = rook;
            }
            if (*strIt == 'K') {
                std::shared_ptr<King> rook = std::make_shared<King>(*strIt);
                mapIt->second = rook;
                white_king = mapIt->first;
            }
            if (*strIt == 'k') {
                std::shared_ptr<King> rook = std::make_shared<King>(*strIt);
                mapIt->second = rook;
                black_king = mapIt->first;
            }
            ++mapIt;
            ++strIt;
        }
    }

    int move_piece(const std::string& from, const std::string& to, bool is_white_turn);
    bool getTurn();
};

#endif // BOARD_H
