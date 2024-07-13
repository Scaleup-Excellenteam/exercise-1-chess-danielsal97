#include "Queen.h"
#include "path_helpers.h"
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <memory>

/// <summary>
/// Checks if the Queen's movement is valid
/// </summary>
/// <param name="board"> The game board </param>
/// <param name="from"> The starting position of the Queen </param>
/// <param name="to"> The target position of the Queen </param>
/// <returns> Status code indicating if the movement is valid or not </returns>
int Queen::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) 
{
    if (from[0] == to[0])
    {
        char start = std::min(from[1], to[1]);
        char end = std::max(from[1], to[1]);
        if (isPathClearVerticalHorizontal(board, from[0], start, end, true)) return validMovement;
    }
    else if (from[1] == to[1]) {
        char start = std::min(from[0], to[0]);
        char end = std::max(from[0], to[0]);
        if (isPathClearVerticalHorizontal(board, from[1], start, end, false)) return validMovement;
        
    }
    else if (std::abs(from[0] - to[0]) == std::abs(from[1] - to[1])) {
        if (isPathClearDiagonal(board, from[0], from[1], to[0], to[1])) return validMovement;
        
    }
    return InvalidMovement; 
}
