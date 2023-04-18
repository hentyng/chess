#include <iostream>
#include <cmath>
#include <string>

enum Piece{
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king,
    nopiece,
};
enum Colour{
    white,
    black,
    nocolour,
	holder,
};

class Square{

Piece piece;
Colour colour;
int x;
int y;

public: 
    void setSquare(Square*);
    void setEmpty();
    void setPieceAndColor(Piece, Colour);
	Piece getPiece();
	Colour getColour();
	void setX(int ex) { x = ex; }
	void setY(int why) { y = why; }
	int getX() { return x; }
	int getY() { return y; }
	Square(){
		piece = nopiece;
    	colour = nocolour;
		//std::cout << "square has been made" << std::endl;
		
	}
};

class Board{

	Square board[8][8];
	Colour turn = white;
	bool moveKing(Square* currentKing, Square* newSquare);
	bool moveQueen(Square* currentQueen, Square* newSquare);
	bool moveBishop(Square* currentBishop, Square* newSquare);
	bool moveKnight(Square* currentKnight, Square* newSquare);
	bool moveRook(Square* currentRook, Square* newSquare);
	bool movePawn(Square* currentPawn, Square* newSquare);
	bool makeMove(int x1, int y1, int x2, int y2);
	void printBoard();
	
	



public:
	Square* getSquare(int x, int y) {
		return &board[x][y];
	}
	void setSquare(Square * s, int x, int y){
		board[x][y]=*s;
	}
	bool doMove();
	void setBoard();
	bool playGame();
	bool notvalid = false;
	bool stopgame = false;
	Board(){
		//std::cout<< "Board has been made" << std::endl;
	}
	
    
};









