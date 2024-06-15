#include "Board.h"


/// <summary>
/// initilize board:
/// 1. create keys values for board game
/// 2. go over "start" and init the game board with all pieces 
/// </summary>
/// <param name="start"> indicte to the start string for init the board</param>
Board::Board(const std::string& start) {
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
            white_king_location = mapIt->first;
        }
        if (*strIt == 'k') {
            std::shared_ptr<King> rook = std::make_shared<King>(*strIt);
            mapIt->second = rook;
            black_king_location = mapIt->first;
        }
        if (*strIt == 'B' || *strIt == 'b') {
            std::shared_ptr<Bishop> bishop = std::make_shared<Bishop>(*strIt);
            mapIt->second = bishop;
        }
        if (*strIt == 'Q' || *strIt == 'q') {
            std::shared_ptr<Queen> queen = std::make_shared<Queen>(*strIt);
            mapIt->second = queen;
        }
        if (*strIt == 'N' || *strIt == 'n') {
            std::shared_ptr<Knight> knight = std::make_shared<Knight>(*strIt);
            mapIt->second = knight;
        }
        if (*strIt == 'P' || *strIt == 'p') {
            std::shared_ptr<Pawn> pawn = std::make_shared<Pawn>(*strIt);
            mapIt->second = pawn;
        }
        ++mapIt;
        ++strIt;
    }
}
/// <summary>
/// this section of code makes move if legal and returns message val
/// it maing moves by logic so after it makes move, it checks if the move is legal:
/// 1. if the move will casue self  checkmate it will undo it and return to user 31 signal
/// 2. if the move will cause check to the opponent it will return 41 signal
/// 3. else it will return 42 signal
/// 
/// </summary>
/// <param name="from"> get the location of piece you want to move </param>
/// <param name="to"> get your target location  </param>
/// <param name="is_white_turn"> which player is playing, helps to know whose turn is now and to set the next turn </param>
/// <returns></returns>
int Board::move_piece(const std::string& from, const std::string& to, bool is_white_turn) {
    if (BoardGame[from] == nullptr) return 11;
    if (BoardGame[from]->getColor() != is_white_turn) return 12;
    if (BoardGame[to] != nullptr && BoardGame[from]->getColor() == BoardGame[to]->getColor()) return 13;
    int res = BoardGame[from]->valid_movment(BoardGame, from, to);
    if (res == 21) return 21;
    if (res == 42) {
        if (BoardGame[from]->Pname == 'K') {
            white_king_location = to;
        }
        else if (BoardGame[from]->Pname == 'k') {
            black_king_location = to;
        }
        BoardGame[to] = BoardGame[from];
        BoardGame[from] = nullptr;
        turn = !turn;
        if (BoardGame[to]->getColor()) {
            res = check_cause_checkmate(BoardGame, white_king_location);
            if (res == 31) {
                BoardGame[from] = BoardGame[to];
                BoardGame[to] = nullptr;
                turn = !turn;
                return 31;
            }
            return check_cause_check(BoardGame, black_king_location);
        }
        else {
                res = check_cause_checkmate(BoardGame, black_king_location);
                if (res == 31) {
                    BoardGame[from] = BoardGame[to];
                    BoardGame[to] = nullptr;
                    turn = !turn;
                    return 31;
                }
                return check_cause_check(BoardGame, white_king_location);    
        }
    }
    return res;
}

bool Board::getTurn() {
    return turn;
}
/// <summary>
/// checks if there is check on your opponent king.
///   itterate over  player pieces and check if there valid move on his king
/// </summary>
/// <param name="board"> get the borad game.</param>
/// <param name="king_location"> get opponent king location</param>
/// <returns></returns>
int Board::check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location) {
    int king_color = board.find(king_location)->second->getColor();
    for (const auto& piece : board) {
        if (piece.second != nullptr and piece.second->getColor() != king_color and piece.second->valid_movment(board, piece.first, king_location) == 42) {
            return 41;
        }
    }
    return 42;
}

/// <summary>
/// check if there is any check of the player king.
/// itterate over opponent pieces and check if there valid move on player king
/// </summary>
/// <param name="board">get the gae board</param>
/// <param name="king_location"> get the player king location</param>
/// <returns></returns>
int Board::check_cause_checkmate(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location) {
    int king_color = board.find(king_location)->second->getColor();
    for (const auto& piece : board)
        if (piece.second != nullptr and piece.second->getColor() != king_color and piece.second->valid_movment(board, piece.first, king_location) == 42) {
            return 31;
        }
    return 42;
}