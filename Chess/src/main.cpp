#include "Chess.h"
#include "Board.h"
#include "CustomExceptions.h"
#include <iostream>

int main() {
    try {
        string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
        string moveMessage;
        Chess a(board);
        Board b(board);
        int codeResponse = 0;
        bool is_white_turn = true;
        auto suggestions = b.suggest_moves(is_white_turn, 5, 2);
        if (suggestions.size() > 0) {
            auto suggestedMove = suggestions.poll();
            moveMessage = "Recommended move: " + suggestedMove.from + suggestedMove.to;
        }
        else {
            moveMessage = "No suggested move available.";
        }
        string res = a.getInput(moveMessage);

        while (res != "exit") {
            codeResponse = b.move_piece(res.substr(0, 2), res.substr(2, 4), is_white_turn);
            is_white_turn = b.getTurn();

            a.setCodeResponse(codeResponse);
            suggestions = b.suggest_moves(is_white_turn, 5, 2);
            if (suggestions.size() > 0) {
                auto suggestedMove = suggestions.poll();
                moveMessage = "Recommended move: " + suggestedMove.from + suggestedMove.to;
            }
            else {
                moveMessage = "No suggested move available.";
            }
            res = a.getInput(moveMessage);
        }

        cout << endl << "Exiting " << endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

