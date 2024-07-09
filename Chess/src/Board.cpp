#include "Board.h"


/// <summary>
/// initilize board:
/// 1. create keys values for board game
/// 2. go over "start" and init the game board with all pieces 
/// </summary>
/// <param name="start"> indicte to the start string for init the board</param>

Board::Board(const std::string& start) {
    king_in_check = 2;
    // Initialize the board with empty squares
    for (char row = '1'; row <= '8'; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            std::string key = std::string(1, col) + row;
            BoardGame[key] = nullptr;
        }
    }

    auto mapIt = BoardGame.begin();
    auto strIt = start.begin();
    while (mapIt != BoardGame.end() && strIt != start.end()) {
        char pieceType = *strIt;
        mapIt->second = createPiece(pieceType);
        if (pieceType == 'K') {
            white_king_location = mapIt->first;
        }
        else if (pieceType == 'k') {
            black_king_location = mapIt->first;
        }
        ++mapIt;
        ++strIt;
    }
}

std::shared_ptr<Piece> Board::createPiece(char pieceType) {
    switch (pieceType) {
    case 'R':
    case 'r':
        return std::make_shared<Rook>(pieceType);
    case 'K':
        return std::make_shared<King>(pieceType);
    case 'k':
        return std::make_shared<King>(pieceType);
    case 'B':
    case 'b':
        return std::make_shared<Bishop>(pieceType);
    case 'Q':
    case 'q':
        return std::make_shared<Queen>(pieceType);
    case 'N':
    case 'n':
        return std::make_shared<Knight>(pieceType);
    case 'P':
    case 'p':
        return std::make_shared<Pawn>(pieceType);
    default:
        return nullptr;
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
    int validation_res = check_Checkmate(is_white_turn, BoardGame);
    if (validation_res != 42) return validation_res;

    if (are_casteling_piece(from, to)) {
        validation_res = casteling(from, to, is_white_turn, BoardGame);
    }
    if (validation_res != 42) return validation_res;

    validation_res = validate_move(from, to, is_white_turn);
    if (validation_res != 42) return validation_res;

    perform_move(from, to);

    validation_res = (check_for_self_checkmate(is_white_turn, BoardGame));

    if (validation_res == 31) {
        undo_move(to, from);

        return validation_res;
    }
    int opponent_check_res = check_opponent_check(is_white_turn);
    return opponent_check_res;

}

int Board::validate_move(const std::string& from, const std::string& to, bool is_white_turn) {
    if (BoardGame[from] == nullptr) return 11; // No piece at source
    if (BoardGame[from]->getColor() != is_white_turn) return 12; // Not player's turn

    if (BoardGame[to] != nullptr && BoardGame[from]->getColor() == BoardGame[to]->getColor()) return 13; // Same color at destination

    int res = BoardGame[from]->valid_movment(BoardGame, from, to);
    if (res != 42) return res; // Invalid move

    return 42; // Valid move
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
    bool king_color = BoardGame[king_location]->getColor();
    for (const auto& piece : board) {
        if (BoardGame[piece.first] != nullptr and BoardGame[piece.first]->getColor() != king_color and BoardGame[piece.first]->valid_movment(board, piece.first, king_location) == 42) {
            return 41;
        }
    }
    king_in_check = 2;
    return 42;
}

/// <summary>
/// check if there is any check of the player king.
/// itterate over opponent pieces and check if there valid move on player king
/// </summary>
/// <param name="board">get the gae board</param>
/// <param name="king_location"> get the player king location</param>
/// <returns></returns>
int Board::check_cause_checkmate(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& king_location) {
    if (board.find(king_location) == board.end() || board.at(king_location) == nullptr) {
        std::cerr << "Error: King location is invalid or king is nullptr" << std::endl;
        return 42; // Indicate error or invalid state
    }

    bool king_color = board.at(king_location)->getColor();
    for (const auto& piece : board) {
        if (piece.second == nullptr) continue;
        if (piece.second->getColor() != king_color && piece.second->valid_movment(board, piece.first, king_location) == 42) {
            return 31; // Checkmate
        }
    }

    return 42; // No checkmate
}
void Board::change_turn() {
    turn = !turn;
}

void Board::perform_move(const std::string& from, const std::string& to) {
    update_king_location(from, to);
    make_move(from, to);
}
void Board::undo_move(const std::string& from, const std::string& to) {
    update_king_location(from, to);
    make_move(from, to);
}
void Board::make_move(const std::string& from, const std::string& to) {
    BoardGame[to] = BoardGame[from];
    BoardGame[from] = nullptr;
    change_turn();
}

void Board::update_king_location(const string& from, const string& to) {
    char king_type = BoardGame[from]->Pname;
    if (BoardGame[from]->Pname == 'K') {
        white_king_location = to;
    }
    else if (BoardGame[from]->Pname == 'k') {
        black_king_location = to;
    }
}

bool Board::is_clear_path(const string& from, const string& to) {
    char row = from[0];
    for (char col = from[1] + 1; col < to[1]; col++) {
        if (BoardGame[string(1, row) + col] != nullptr)
            return false;
    }
    return true;
}
bool Board::are_casteling_piece(const std::string& from, const std::string& to) {
    auto fromPiece = BoardGame[from];
    auto toPiece = BoardGame[to];

    return (dynamic_cast<King*>(fromPiece.get()) && dynamic_cast<Rook*>(toPiece.get())) ||
        (dynamic_cast<Rook*>(fromPiece.get()) && dynamic_cast<King*>(toPiece.get()));
}




int Board::casteling(const std::string& from, const std::string& to, bool is_white_turn, std::map<std::string, std::shared_ptr<Piece>>& board) {
    std::string command = from + to;
    if (from > to) {
        command = to + from;
    }
    else if (is_clear_path(command.substr(0, 2), command.substr(2, 2))) {
        auto it = castlingMoves.find(command);
        if (it != castlingMoves.end()) {
            const auto& move = it->second;

            update_king_location(move.kingFrom, move.kingTo);
            auto temp_kingTo = BoardGame[move.kingTo];
            auto temp_rookTo = BoardGame[move.rookTo];
            BoardGame[move.kingTo] = BoardGame[move.kingFrom];
            BoardGame[move.kingFrom] = nullptr;
            BoardGame[move.rookTo] = BoardGame[move.rookFrom];
            BoardGame[move.rookFrom] = nullptr;
            change_turn();
            int validation_res = (check_for_self_checkmate(is_white_turn, board));
            if (validation_res == 42) return 43;
            update_king_location(move.kingTo, move.kingFrom);

            BoardGame[move.kingFrom] = BoardGame[move.kingTo];
            BoardGame[move.kingTo] = temp_kingTo;
            BoardGame[move.rookFrom] = BoardGame[move.rookTo];
            BoardGame[move.rookTo] = temp_rookTo;
            change_turn();

            return 31;
        }
    }
    return 21;
}

int Board::check_Checkmate(bool is_white_turn, std::map<std::string, std::shared_ptr<Piece>>& board) {
    std::string king_loc = is_white_turn ? white_king_location : black_king_location;

    for (const auto& piece : board) {
        if (piece.second == nullptr || piece.second->getColor() != is_white_turn) continue;

        std::string from = piece.first;

        for (const auto& sec_piece : board) {
            std::string to = sec_piece.first;
            if (from == to) continue;

            int validation_res = validate_move(from, to, is_white_turn);
            if (validation_res != 42) continue;

            // Simulate the move on a copy of the board
            auto originalFrom = board[from];
            auto originalTo = board[to];
            update_king_location(from, to);
            board[to] = board[from];
            board[from] = nullptr;

            // Check for self checkmate on the temporary board
            int move_result = check_for_self_checkmate(is_white_turn, board);

            // Undo the move
            update_king_location(to, from);

            board[from] = originalFrom;
            board[to] = originalTo;

            if (move_result == 42) {
                //      int a;
                  //    cout <<endl<< "from: " << from << " to: " << to<<endl;
                    //  cin >> a;
                return 42; // Found a valid move to avoid checkmate
            }
        }
    }

    std::cout << "Checkmate detected for " << (is_white_turn ? "white" : "black") << std::endl;
    std::cout << "The winner is: " << (!is_white_turn ? "white" : "black") << std::endl;
    return 44; // Checkmate
}

int Board::check_for_self_checkmate(bool is_white_turn, const std::map<std::string, std::shared_ptr<Piece>>& board) {
    return check_cause_checkmate(board, is_white_turn ? white_king_location : black_king_location);
}



int Board::check_opponent_check(bool is_white_turn) {
    if (is_white_turn) {
        return check_cause_check(BoardGame, black_king_location);
    }
    else {
        return check_cause_check(BoardGame, white_king_location);
    }

}