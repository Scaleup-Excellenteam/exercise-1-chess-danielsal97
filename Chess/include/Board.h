#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "Piece.h"
#include "Rook.h"

class Board {
    std::map<std::string, std::shared_ptr<Piece>> BoardGame;

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
            ++mapIt;
            ++strIt;
        }
    }

    const auto& getBoard() const {
        return BoardGame;
    }
    int move_piece(const string& from, const string& to, int is_white_turn) {
        int res;
        if (BoardGame[from] == nullptr) return 11;
        if (BoardGame[to] != nullptr and BoardGame[from]->getColor() == BoardGame[to]->getColor()) return 13;
        res = BoardGame[from]->valid_movment(BoardGame, from, to);
        if (res == 42) {
            BoardGame[to] = BoardGame[from];
            BoardGame[from] = nullptr;
            return 42;
        }
    }
};
