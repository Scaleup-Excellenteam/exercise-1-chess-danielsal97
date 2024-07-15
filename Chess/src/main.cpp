#include "Chess.h"
#include "Board.h"
#include "CustomExceptions.h"
#include <iostream>
std::string getMoveMessage(PriorityQueue<Move, MyComparator>& suggestions) {
    std::string message = "Recommended moves: ";
    int count = 0;

    while (count < 3 && suggestions.size() > 0) {
        auto suggestedMove = suggestions.poll();
        if (count > 0) {
            message += ", ";
        }
        message += suggestedMove.from + suggestedMove.to;
        count++;
    }

    if (count == 0) {
        return "No suggested move available.";
    }

    return message;
}
int main() {
    std::string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    std::string moveMessage;
    Chess a(board);
    Board b(board);
    int codeResponse = 0;
    bool is_white_turn = true;
    auto suggestions = b.suggest_moves(is_white_turn, 5, 2);


    std::string res = a.getInput(getMoveMessage(suggestions));
    

    while (res != "exit") {
        try {
            codeResponse = b.move_piece(res.substr(0, 2), res.substr(2, 2), is_white_turn);
            is_white_turn = b.getTurn();

            a.setCodeResponse(codeResponse);
            suggestions = b.suggest_moves(is_white_turn, 5, 2);

            res = a.getInput(getMoveMessage(suggestions));
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            moveMessage = e.what();
            res = a.getInput(moveMessage);
        }
    }
    std::cout << "Exiting " << std::endl;
    return 0;
}
