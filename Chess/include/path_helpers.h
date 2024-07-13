#ifndef PATH_HELPERS_H
#define PATH_HELPERS_H

#include <map>
#include <string>
#include <memory>
#include "Piece.h"

bool isPathClearVerticalHorizontal(const std::map<std::string, std::shared_ptr<Piece>>& board, char fixed, char start, char end, bool isVertical);
bool isPathClearDiagonal(const std::map<std::string, std::shared_ptr<Piece>>& board, char startX, char startY, char endX, char endY);

#endif // PATH_HELPERS_H
