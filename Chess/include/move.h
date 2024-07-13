#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>

class Move {
public:
    std::string from;
    std::string to;
    int score;

    Move(const std::string& from, const std::string& to)
        : from(from), to(to), score(0) {}

    bool operator<(const Move& other) const {
        return score < other.score;
    }

    bool operator>(const Move& other) const {
        return score > other.score;
    }

    friend std::ostream& operator<<(std::ostream& os, const Move& move) {
        os << move.from << " -> " << move.to << " (Score: " << move.score << ")";
        return os;
    }
};

#endif // MOVE_H
