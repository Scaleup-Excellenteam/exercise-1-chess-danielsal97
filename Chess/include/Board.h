#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <string>
#include <memory>
#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"
struct CastlingMove {
    std::string rookFrom;
    std::string kingTo;
    std::string rookTo;
    std::string kingFrom;
};
class Board {
    std::map<std::string, std::shared_ptr<Piece>> BoardGame;
    bool turn = true;
    std::string white_king_location, black_king_location;
    std::map<std::string, CastlingMove> castlingMoves = {
    {"a1a5", {"a1", "a3", "a4", "a5"}},
    {"h1h5", {"h1", "h3", "h4", "h5"}},
    {"a5a8", {"a5", "a6", "a7", "a8"}},
    {"h5h8", {"h5", "h6", "h7", "h8"}}
    };
    bool black_check_flag = false, white_check_flag = false;
public:
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
    explicit Board(const std::string& start);
    std::shared_ptr<Piece> createPiece(char pieceChar);
    int move_piece(const std::string& from, const std::string& to, bool is_white_turn);
    bool getTurn();
    int check_cause_checkmate(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& king_location);
    int check_cause_check(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& king_location);
    void change_turn();
    void make_move(const string& from, const string& to);
    void update_king_location(const string& from, const string& to);
    int casteling(const std::string& from, const std::string& to, bool is_white_turn, std::map<std::string, std::shared_ptr<Piece>>& board);
    bool is_clear_path(const string& from, const string& to);
    bool are_casteling_piece(const string& from, const string& to);
    int check_Checkmate(bool is_white_turn, map<std::string, std::shared_ptr<Piece>>& board);
    int validate_move(const std::string& from, const std::string& to, bool is_white_turn);
    void perform_move(const std::string& from, const std::string& to);
    int check_opponent_check(bool is_white_turn);
    void undo_move(const std::string& from, const std::string& to, const shared_ptr<Piece>& original_from, const shared_ptr<Piece>& original_to);
    int check_for_self_checkmate(bool is_white_turn, const std::map<std::string, std::shared_ptr<Piece>>& board);
    bool is_castling_allowed(bool is_white_turn) const;
    bool has_piece_moved(const std::string& position, const std::map<std::string, std::shared_ptr<Piece>>& board) const;
    void set_check_flag(bool is_white_turn);
    map<string, bool> check_has_piece_moved();
    void revert_has_moved_changes(map<string, bool> locations);
    void revert_checkmate_flags(bool is_white_turn);
    void revert_casteling_flags(map<string, bool> locations, bool is_white_turn);
};

#endif // BOARD_H
