#include "Board.h"
#include "CustomExceptions.h"
#include <array>

/// <summary>
/// Initializes the board:
/// 1. Creates keys for the board game
/// 2. Goes over the "start" string and initializes the game board with all pieces 
/// </summary>
/// <param name="start"> Indicates the start string for initializing the board</param>

Board::Board(const std::string& start) {
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
        update_king_location(mapIt->first, mapIt->first);

        ++mapIt;
        ++strIt;
    }
}

std::shared_ptr<Piece> Board::createPiece(char pieceType) {
    switch (pieceType) {
    case 'R': case 'r': return std::make_shared<Rook>(pieceType);
    case 'K': return std::make_shared<King>(pieceType);
    case 'k': return std::make_shared<King>(pieceType);
    case 'B': case 'b': return std::make_shared<Bishop>(pieceType);
    case 'Q': case 'q': return std::make_shared<Queen>(pieceType);
    case 'N': case 'n': return std::make_shared<Knight>(pieceType);
    case 'P': case 'p': return std::make_shared<Pawn>(pieceType);
    default: return nullptr;
    }
}

/// <summary>
/// Makes a move if legal and returns a status code:
/// 1. If the move will cause self-checkmate, it will undo it and return a signal of 31
/// 2. If the move will cause check to the opponent, it will return a signal of 41
/// 3. Otherwise, it will return validMovement signal
/// </summary>
/// <param name="from"> Location of the piece you want to move </param>
/// <param name="to"> Target location </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <returns> Status code indicating the result of the move </returns>
int Board::move_piece(const std::string& from, const std::string& to, bool is_white_turn) {
    map<string, bool> original_moves_data = check_has_piece_moved();
    int validation_res = check_Checkmate(is_white_turn, BoardGame);
    if (validation_res != validMovement) {
        is_white_turn ? white_check_flag = true : black_check_flag = true;
        return validation_res;
    }
    revert_casteling_flags(original_moves_data, is_white_turn);
    if (are_casteling_piece(from, to)) {
        validation_res = casteling(from, to, is_white_turn, BoardGame);
    }
    if (validation_res != validMovement) {
        return validation_res;
    }
    validation_res = validate_move(from, to, is_white_turn);
    if (validation_res != validMovement) return validation_res;
    auto original_form = BoardGame[from];
    auto original_to = BoardGame[to];

    perform_move(from, to);
    validation_res = (check_for_self_checkmate(is_white_turn, BoardGame));
    if (validation_res == ImmediateCheck) {
        undo_move(to, from, original_form, original_to);
        revert_casteling_flags(original_moves_data, is_white_turn);

        is_white_turn ? white_check_flag = true : black_check_flag = true;
        return validation_res;
    }
    int opponent_check_res = check_opponent_check(is_white_turn);

    set_check_flag(is_white_turn);
    return opponent_check_res;
}

/// <summary>
/// Validates the move from the source to the destination
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <returns> Status code indicating if the move is valid or not </returns>
int Board::validate_move(const std::string& from, const std::string& to, bool is_white_turn) {
    if (BoardGame[from] == nullptr) return NoPieceAtSource;
    if (BoardGame[from]->getColor() != is_white_turn) return NotYourTurn;
    if (BoardGame[to] != nullptr && BoardGame[from]->getColor() == BoardGame[to]->getColor()) return InvalidDestination; // Same color at destination

    int res = BoardGame[from]->valid_movment(BoardGame, from, to);
    if (res != validMovement) return res;
    return validMovement;
}


bool Board::getTurn() {
    return turn;
}

/// <summary>
/// Checks if there is a check on the opponent's king by iterating over player pieces and checking if there is a valid move on the opponent's king
/// </summary>
/// <param name="board"> The game board </param>
/// <param name="king_location"> Opponent king location </param>
/// <returns> Status code indicating if there is a check on the opponent's king </returns>
int Board::check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const string& king_location) {
    bool king_color = BoardGame[king_location]->getColor();
    for (const auto& piece : board) {
        auto p = BoardGame[piece.first];
        if (p != nullptr && p->getColor() != king_color && p->valid_movment(board, piece.first, king_location) == validMovement) {
            return CheckToOpponent;
        }
    }
    return validMovement;
}

/// <summary>
/// Checks if there is a checkmate on the player's king by iterating over opponent pieces and checking if there is a valid move on the player's king
/// </summary>
/// <param name="board"> The game board </param>
/// <param name="king_location"> The player's king location </param>
/// <returns> Status code indicating if there is a checkmate on the player's king </returns>
int Board::check_cause_checkmate(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& king_location) {
    if (board.find(king_location) == board.end() || board.at(king_location) == nullptr) {
        std::cerr << "Error: King location is invalid or king is nullptr" << std::endl;
        return validMovement;
    }
    bool king_color = board.at(king_location)->getColor();
    for (const auto& piece : board) {
        if (piece.second == nullptr) continue;
        if (piece.second->getColor() != king_color && piece.second->valid_movment(board, piece.first, king_location) == validMovement) {
            return ImmediateCheck;
        }
    }

    return validMovement;
}

/// <summary>
/// Changes the turn to the next player
/// </summary>
void Board::change_turn() {
    turn = !turn;
}

/// <summary>
/// Performs the move from the source to the destination and updates the king's location if necessary
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
void Board::perform_move(const std::string& from, const std::string& to) {
    update_king_location(from, to);
    make_move(from, to);
}

/// <summary>
/// Updates the king's location if the move involves a king
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
void Board::update_king_location(const string& from, const string& to) {
    if (BoardGame[from] == nullptr) return;
    char king_type = BoardGame[from]->Pname;
    if (king_type == 'K') {
        white_king_location = to;
    }
    else if (king_type == 'k') {
        black_king_location = to;
    }
}

/// <summary>
/// Checks if the path is clear for a move from the source to the destination
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
/// <returns> True if the path is clear, false otherwise </returns>
bool Board::is_clear_path(const string& from, const string& to) {
    char row = from[0];
    for (char col = from[1] + 1; col < to[1]; col++) {
        if (BoardGame[string(1, row) + col] != nullptr)
            return false;
    }
    return true;
}

/// <summary>
/// Checks if the move involves castling
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
/// <returns> True if the move involves castling, false otherwise </returns>
bool Board::are_casteling_piece(const std::string& from, const std::string& to) {
    auto fromPiece = BoardGame[from];
    auto toPiece = BoardGame[to];

    return (dynamic_cast<King*>(fromPiece.get()) && dynamic_cast<Rook*>(toPiece.get())) ||
        (dynamic_cast<Rook*>(fromPiece.get()) && dynamic_cast<King*>(toPiece.get()));
}


/// <summary>
/// Handles castling moves if legal, otherwise throws an exception
/// </summary>
/// <param name="from"> Location of the piece you want to move </param>
/// <param name="to"> Target location </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <param name="board"> Current state of the board </param>
/// <returns> Status code indicating the result of the move </returns>
int Board::casteling(const std::string& from, const std::string& to, bool is_white_turn, std::map<std::string, std::shared_ptr<Piece>>& board) {
  
        std::string command = from + to;
        if (from > to) {
            command = to + from;
        }

        if (!is_clear_path(command.substr(0, 2), command.substr(2, 2))) {
            throw InvalidCastlingException("Path is not clear for castling.");
        }

        auto it = castlingMoves.find(command);
        if (it == castlingMoves.end()) {
            throw InvalidCastlingException("Invalid castling move.");
        }

        const auto& move = it->second;

        if (!is_castling_allowed(is_white_turn) || has_piece_moved(move.kingFrom, board) || has_piece_moved(move.rookFrom, board)) {
            throw InvalidCastlingException("Castling not allowed due to previous moves or rules.");
        }

        update_king_location(move.kingFrom, move.kingTo);

        // Store original values, for undoing it in cases that move causes check
        auto temp_kingFrom = BoardGame[move.kingFrom];
        auto temp_kingTo = BoardGame[move.kingTo];
        auto temp_rookFrom = BoardGame[move.rookFrom];
        auto temp_rookTo = BoardGame[move.rookTo];

        perform_move(move.kingFrom, move.kingTo);
        perform_move(move.rookFrom, move.rookTo);
        change_turn();

        int validation_res = check_for_self_checkmate(is_white_turn, board);
        if (validation_res == validMovement) {
            return valid_casteling;
        }

        // Undo the moves if it causes a check
        update_king_location(move.kingTo, move.kingFrom);
        undo_move(move.kingFrom, move.kingTo, temp_kingFrom, temp_kingTo);
        undo_move(move.rookFrom, move.rookTo, temp_rookFrom, temp_rookTo);
        change_turn();

        throw IllegalMoveException("Move causes self-checkmate.");
    


}

/// <summary>
/// Checks if the current player's king is in checkmate
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <param name="board"> The game board </param>
/// <returns> Status code indicating if the current player's king is in checkmate </returns>
int Board::check_Checkmate(bool is_white_turn, std::map<std::string, std::shared_ptr<Piece>>& board) {
    std::string king_loc = is_white_turn ? white_king_location : black_king_location;

    for (const auto& piece : board) {
        if (piece.second == nullptr || piece.second->getColor() != is_white_turn) continue;

        std::string from = piece.first;

        for (const auto& sec_piece : board) {
            std::string to = sec_piece.first;
            if (from == to) continue;
            int validation_res = validate_move(from, to, is_white_turn);
            if (validation_res != validMovement) continue;
            auto originalFrom = board[from];
            auto originalTo = board[to];
            update_king_location(from, to);
            perform_move(from, to);
            int move_result = check_for_self_checkmate(is_white_turn, board);
            update_king_location(to, from);
            undo_move(from, to, originalFrom, originalTo);
            if (move_result == validMovement) {
                return validMovement;
            }
        }
    }
    cout << "Checkmate detected for " << (is_white_turn ? "white" : "black") << endl;
    cout << "The winner is: " << (!is_white_turn ? "white" : "black") << endl;

    return Checkmate;
}

/// <summary>
/// Checks if a move will result in self-checkmate
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <param name="board"> The game board </param>
/// <returns> Status code indicating if a move will result in self-checkmate </returns>
int Board::check_for_self_checkmate(bool is_white_turn, const std::map<std::string, std::shared_ptr<Piece>>& board) {
    return check_cause_checkmate(board, is_white_turn ? white_king_location : black_king_location);
}

/// <summary>
/// Checks if the opponent's king is in check
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <returns> Status code indicating if the opponent's king is in check </returns>
int Board::check_opponent_check(bool is_white_turn) {
    return check_cause_check(BoardGame, is_white_turn ? black_king_location : white_king_location);
}

/// <summary>
/// Undoes a move and reverts the board to its previous state
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
/// <param name="fromPiece"> Piece at the source location before the move </param>
/// <param name="toPiece"> Piece at the destination location before the move </param>
void Board::undo_move(const std::string& from, const std::string& to, const shared_ptr<Piece>& fromPiece, const shared_ptr<Piece>& toPiece) {
    update_king_location(to, from);
    BoardGame[from] = fromPiece;
    BoardGame[to] = toPiece;
    change_turn();
}

/// <summary>
/// Makes a move from the source to the destination
/// </summary>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
void Board::make_move(const std::string& from, const std::string& to) {
    BoardGame[to] = BoardGame[from];
    BoardGame[from] = nullptr;
    change_turn();
}

/// <summary>
/// Checks if castling is allowed for the current player
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <returns> True if castling is allowed, false otherwise </returns>
bool Board::is_castling_allowed(bool is_white_turn) const {
    return !(is_white_turn ? white_check_flag : black_check_flag);
}

/// <summary>
/// Checks if a piece at a given position has moved
/// </summary>
/// <param name="position"> Position of the piece </param>
/// <param name="board"> The game board </param>
/// <returns> True if the piece has moved, false otherwise </returns>
bool Board::has_piece_moved(const std::string& position, const std::map<std::string, std::shared_ptr<Piece>>& board) const {
    return board.at(position)->has_moved;
}

/// <summary>
/// Checks and returns a map of pieces that have not moved from their initial positions
/// </summary>
/// <returns> A map of pieces that have not moved </returns>
map<string, bool> Board::check_has_piece_moved() {
    std::array<std::string, 6> locations = { "a1", "a5", "a8", "h1", "h5", "h8" };
    map<string, bool> check;

    for (const auto& loc : locations) {
        if (BoardGame[loc] == nullptr) continue;
        if (!BoardGame[loc]->has_moved)
            check[loc] = false;
    }
    return check;
}

/// <summary>
/// Reverts the moved status of pieces based on the given map
/// </summary>
/// <param name="locations"> Map of pieces that have not moved </param>
void Board::revert_has_moved_changes(map<string, bool> locations) {
    for (const auto& piece : locations) {
        if (BoardGame[piece.first] == nullptr) continue;
        BoardGame[piece.first]->has_moved = false;
    }
}

/// <summary>
/// Sets the check flag for the current player
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
void Board::set_check_flag(bool is_white_turn) {
    is_white_turn ? white_check_flag = true : black_check_flag = true;
}

/// <summary>
/// Reverts the check flags for the current player
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
void Board::revert_checkmate_flags(bool is_white_turn) {
    is_white_turn ? white_check_flag = false : black_check_flag = false;
}

/// <summary>
/// Reverts the castling flags and moved status of pieces based on the given map
/// </summary>
/// <param name="locations"> Map of pieces that have not moved </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
void Board::revert_casteling_flags(map<string, bool> locations, bool is_white_turn) {
    revert_has_moved_changes(locations);
    revert_checkmate_flags(is_white_turn);
}
/// <summary>
/// Evaluates a move and updates its score
/// </summary>
/// <param name="move"> The move to evaluate </param>
/// <param name="from"> Source location </param>
/// <param name="to"> Destination location </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <param name="depth"> Depth for move evaluation </param>
void Board::evaluate_move(Move& move, const string& from, const string& to, bool is_white_turn, int depth) {
    auto originalFrom = BoardGame[from];
    auto originalTo = BoardGame[to];
    perform_move(from, to);

    if (check_for_self_checkmate(is_white_turn, BoardGame) == ImmediateCheck) {
        move.score -= originalFrom->score;
    }
    else {
        check_danger(move, to, is_white_turn);
        check_threats(move, to, originalFrom, is_white_turn);

        if (controls_center(to)) {
            move.score += 5; 
        }
        int coverage_difference = calculate_coverage(is_white_turn) - calculate_coverage(!is_white_turn);
        move.score += coverage_difference;

        if (depth > 0) {
            auto opponentMoves = suggest_moves(!is_white_turn, 5, depth - 1);
            if (opponentMoves.size() > 0) {
                auto bestOpponentMove = opponentMoves.poll();
                move.score -= bestOpponentMove.score;
            }
        }
    }
    undo_move(from, to, originalFrom, originalTo);
}

/// <summary>
/// Checks if a move puts the piece in danger and updates the move's score
/// </summary>
/// <param name="move"> The move to check </param>
/// <param name="to"> Destination location </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
void Board::check_danger(Move& move, const std::string& to, bool is_white_turn) {
    for (const auto& opponentPiece : BoardGame) {
        if (opponentPiece.second != nullptr && opponentPiece.second->getColor() != is_white_turn) {
            if (validate_move(opponentPiece.first, to, !is_white_turn) == validMovement) {
                move.score -= opponentPiece.second->score;
            }
        }
    }
}

/// <summary>
/// Checks if a move threatens a stronger opponent piece and updates the move's score
/// </summary>
/// <param name="move"> The move to check </param>
/// <param name="to"> Destination location </param>
/// <param name="originalFrom"> The original piece before the move </param>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
void Board::check_threats(Move& move, const std::string& to, const std::shared_ptr<Piece>& originalFrom, bool is_white_turn)
{
    for (const auto& opponentPiece : BoardGame) {
        if (opponentPiece.second == nullptr || opponentPiece.second->getColor() == is_white_turn) {
            continue;
        }

        std::string opponentFrom = opponentPiece.first;
        if (validate_move(to, opponentFrom, is_white_turn) == validMovement)
        {
            if (opponentPiece.second->score > originalFrom->score)
            {
                move.score += opponentPiece.second->score - originalFrom->score;  // Add points for threatening a stronger opponent piece
            }
        }
    }
}

bool Board::controls_center(const string& position) {
    list <string> center_positions = { "d4", "d5", "e4", "e5" };
    return std::find(center_positions.begin(), center_positions.end(), position) != center_positions.end();
}

int Board::calculate_coverage(bool is_white_turn) {
    int coverage = 0;
    for (const auto& piece : BoardGame) {
        if (piece.second != nullptr && piece.second->getColor() == is_white_turn) {
            for (const auto& target : BoardGame) {
                if (validate_move(piece.first, target.first, is_white_turn) == validMovement) {
                    coverage++;
                }
            }
        }
    }
    return coverage;
}


/// <summary>
/// Suggests the best moves for the current player
/// </summary>
/// <param name="is_white_turn"> Indicates which player's turn it is </param>
/// <param name="max_suggestions"> Maximum number of suggestions to return </param>
/// <param name="depth"> Depth for move evaluation </param>
/// <returns> A priority queue of the best moves </returns>
PriorityQueue<Move, MyComparator> Board::suggest_moves(bool is_white_turn, int max_suggestions, int depth) {
    PriorityQueue<Move, MyComparator> pq;
    auto original_moves_data = check_has_piece_moved();

    for (const auto& piece : BoardGame) {
        if (piece.second == nullptr || piece.second->getColor() != is_white_turn) {
            continue;
        }

        std::string from = piece.first;
        for (const auto& piece2 : BoardGame) {
            std::string to = piece2.first;
            if (from == to) continue;

            if (validate_move(from, to, is_white_turn) != validMovement) {
                continue;
            }

            Move move(from, to);

            if (piece2.second != nullptr) {
                move.score += piece2.second->score;
            }
            evaluate_move(move, from, to, is_white_turn, depth);
            pq.push(move);
        }
    }

    revert_casteling_flags(original_moves_data, is_white_turn);
    return pq;
}

void Board::pawnPromotion(const std::string& to, bool is_white_turn) {
    char pawn = is_white_turn ? 'P' : 'p';
    int last_rank = is_white_turn ? 'h' : 'a';
    if (BoardGame[to]->Pname == pawn && (to[0] - 0) == last_rank) {
        char promotion_choice;
        string legal_pieces = is_white_turn ? "Q, R, B, N" : "q, r, b, n";

        bool valid_choice = false;
        while (!valid_choice) {
            try {
                cout << "Promote pawn to (" << legal_pieces << "): ";
                cin >> promotion_choice;

                if (legal_pieces.find(promotion_choice) == string::npos) {
                    throw InvalidPromotionException("Invalid promotion choice. Please choose Q, R, B, or N.");
                }

                BoardGame[to] = createPiece(promotion_choice);
                valid_choice = true;
            }
            catch (const InvalidPromotionException& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }
}