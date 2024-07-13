// Chess 
#include "Chess.h"
#include "Board.h"

int main() {
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    // string board = "RNBQKBNR################################################rnbqkbnr";
    // string board = "##########K###############################R#############r#r#####";

    string moveMessage;
    Chess a(board);
    Board b(board);
    int codeResponse = 0;
    bool is_white_turn = true;

    // Suggest initial moves
    auto suggestions = b.suggest_moves(is_white_turn, 5);
    if (suggestions.size() > 0) {
        auto suggestedMove = suggestions.poll();
        moveMessage = "Recommended move: " + suggestedMove.from + suggestedMove.to;
    }
    else {
        moveMessage = "No suggested move available.";
    }

    // Get input from the user based on the suggested move
    string res = a.getInput(moveMessage);

    while (res != "exit") {
        // TODO:
        // 1. Create enum for the following code values:
        // Illegal movements:
        // 11 - there is no piece at the source
        // 12 - the piece in the source is a piece of your opponent
        // 13 - there is one of your pieces at the destination
        // 21 - illegal movement of that piece
        // 31 - this movement will cause you checkmate
        // Legal movements:
        // 41 - the last movement was legal and caused a check
        // 42 - the last movement was legal, next turn
        // 44 - checkmate

        // Move the piece and get the response code
        codeResponse = b.move_piece(res.substr(0, 2), res.substr(2, 4), is_white_turn);
        is_white_turn = b.getTurn();

        // Set the response code in the Chess class
        a.setCodeResponse(codeResponse);

        // Suggest moves for the next turn
        suggestions = b.suggest_moves(is_white_turn, 5);
        if (suggestions.size() > 0) {
            auto suggestedMove = suggestions.poll();
            moveMessage = "Recommended move: " + suggestedMove.from + suggestedMove.to;
        }
        else {
            moveMessage = "No suggested move available.";
        }

        // Get input from the user based on the suggested move
        res = a.getInput(moveMessage);
    }

    cout << endl << "Exiting " << endl;
    return 0;
}
