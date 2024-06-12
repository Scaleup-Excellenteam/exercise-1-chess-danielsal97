// Chess 
#include "Chess.h"
#include "Board.h"
int main()
{
	//string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
	string board = "R##K###R################################################r#k####r";

//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	Board b(board);
	int codeResponse = 0;
	string res = a.getInput();
	bool is_white_turn = true;
	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		codeResponse = b.move_piece(res.substr(0, 2), res.substr(2, 4),is_white_turn);
		is_white_turn = b.getTurn();
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}