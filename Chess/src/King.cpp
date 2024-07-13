#include "King.h"

/// <summary>
/// Checks if the King's movement is valid
/// </summary>
/// <param name="board"> The game board </param>
/// <param name="from"> The starting position of the King </param>
/// <param name="to"> The target position of the King </param>
/// <returns> Status code indicating if the movement is valid or not </returns>
int King::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    int row_diff = abs(from[0] - to[0]);
    int col_diff = abs(from[1] - to[1]);

    if (row_diff > 1 || col_diff > 1) {
        return InvalidMovement;
    }

    has_moved = true; // Mark the King as having moved
    return validMovement; 
}
