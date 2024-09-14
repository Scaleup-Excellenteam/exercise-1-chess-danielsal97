#include "Bishop.h"
#include "path_helpers.h"
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <memory>

/// <summary>
/// Checks if the Bishop's movement is valid
/// </summary>
/// <param name="board"> The game board </param>
/// <param name="from"> The starting position of the Bishop </param>
/// <param name="to"> The target position of the Bishop </param>
/// <returns> Status code indicating if the movement is valid or not </returns>
int Bishop::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    if (std::abs(from[0] - to[0]) == std::abs(from[1] - to[1])) {
        if (isPathClearDiagonal(board, from[0], from[1], to[0], to[1])) {
            return validMovement; 
        }
    }
    return InvalidMovement; 
}
