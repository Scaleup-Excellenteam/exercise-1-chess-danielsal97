## Algorithm Explanation

The algorithm aims to suggest the best moves for the current player using a priority queue. The main steps are:

1. **Generate all possible moves:** For each piece on the board, generate all possible valid moves.
2. **Evaluate each move:** For each valid move:
   - **Capturing Opponent Piece:** Add points if the move captures an opponent piece.
   - **Check Danger:** Deduct points if the move puts the piece in danger (either by leading to self-check or making it capturable by an opponent piece).
   - **Check Threats:** Add points if the move threatens a stronger opponent piece.
3. **Use a Priority Queue:** Store the evaluated moves in a priority queue, maintaining a maximum size as specified (e.g., the top 3 moves).
4. **Return Best Moves:** Return the moves with the highest scores.

## Complexity Analysis

- **Generating Moves:** For each piece on the board, we generate all possible moves. In the worst case, this is \(O(n^2)\), where \(n\) is the number of squares on the board (64 for a standard chessboard).
- **Validating Moves:** Each move validation involves checking the rules for that piece and ensuring the path is clear, which is \(O(1)\) per move.
- **Evaluating Moves:** For each move, we check for danger and threats, which involves iterating over the board. Thus, the complexity of evaluating each move is \(O(n)\).
- **Priority Queue Operations:** Inserting into and extracting from the priority queue has a complexity of \(O(\log k)\), where \(k\) is the maximum number of suggestions (e.g., 3).

Therefore, the overall complexity of the algorithm is \(O(n^3 \log k)\) due to the nested loops and the use of the priority queue. This is feasible given the constraints of a standard chess game.

## Custom Exceptions

### InvalidCastlingException
**Description:** InvalidCastlingException is thrown when a castling move is not allowed due to various reasons such as the path not being clear, pieces have moved previously, or castling is not allowed due to game rules.

**Usage:** In the castling method, if any condition for a valid castling move is not met, the InvalidCastlingException is thrown with a message indicating the specific issue.

### InvalidPromotionException
**Description:** InvalidPromotionException is thrown when the promotion choice for a pawn is invalid. This ensures that the pawn is promoted to a valid piece.

**Usage:** In the pawnPromotion method, if the promotion choice does not match one of the valid pieces (Q, R, B, N) for the white plater or (q, r, b, n) for the black player , the InvalidPromotionException is thrown with a message indicating the invalid choice.
