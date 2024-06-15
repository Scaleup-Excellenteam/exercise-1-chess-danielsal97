#include "Queen.h"
int Queen::valid_movment(const std::map<std::string, std::shared_ptr<Piece>>& board, const std::string& from, const std::string& to) {
    int a;
    if (from[0] == to[0]) {
 
        char start = min(from[1], to[1]);
        char end = max(from[1], to[1]) -1;
        cout << "start: " << start << " end: " << end << endl;

        for (char i = start + 1; i < end  ; i++) {
            string pos = from[0] + string(1,i);
            cout << "pos: " << pos << endl<<" i: "<<i<<endl;
            cin >> a;
            if (board.find(pos)->second != nullptr) {
                cout << endl << board.find(pos)->second->Pname;
                cin>>a;
                return 21;
            }
        }
        return 42;
    }
    if (from[1] == to[1]) {
        char start = min(from[0], to[0]);
        char end = max(from[0], to[0]);

        for (char i = start + 1; i < end ; i++) {
            string pos = string(1, i) + from[1];
            if (board.find(pos)->second != nullptr) return 21;
        }
        return 42;
    }
    if (abs(from[0] - to[0]) == abs(from[1] - to[1])) {
        char start_x = min(from[0], to[0]);
        char end_x = max(from[0], to[0]);
        char start_y = min(from[1], to[1]);
        char end_y = max(from[1], to[1]);
        for (char x = start_x + 1, y = start_y + 1; x < end_x && y < end_y; x++, y++) {
            std::string pos = std::string(1, x) + std::string(1, y);

            if (board.find(pos)->second != nullptr) {
 
                return 21; 
            }
        }
        return 42;


    }

    return 21;
}