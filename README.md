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


# Custom Exceptions in Chess Class

## InvalidInputException

### Description
`InvalidInputException` is thrown when the input coordinates are out of bounds. This exception ensures that the input provided by the user is valid and within the acceptable range for a chessboard.

### Usage
In the `isValid` method, if the input coordinates are found to be out of the acceptable range, the `InvalidInputException` is thrown with a message indicating that the input is invalid due to out-of-bounds coordinates.

---

## IllegalMoveException

### Description
`IllegalMoveException` is thrown when the source and destination coordinates are the same. This exception ensures that a piece is not moved to the same location it started from.

### Usage
In the `isSame` method, if the source and destination coordinates are identical, the `IllegalMoveException` is thrown with a message indicating that the move is invalid because the source and destination are the same.
