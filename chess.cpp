#include <iostream>
#include "chess.h"



void Square::setEmpty(){
    piece = nopiece;
    colour = nocolour;
}

void Square::setSquare(Square* square){
    piece = square->getPiece();
    colour = square->getColour();
}

void Square::setPieceAndColor(Piece p, Colour c){
    piece = p;
    colour = c;
}

Piece Square::getPiece(){
    return piece;
}

Colour Square::getColour(){
    return colour;
}
bool Board::moveKing(Square* currentKing, Square* newSquare){
	int kingX = currentKing->getX();
	int kingY = currentKing->getY();
	int newX = newSquare->getX();
	int newY = newSquare->getY();
	bool invalid = false;
	Colour holder = currentKing->getColour();

	if (abs(kingX - newX) >1){
			notvalid = true;
			return false;
		if(abs(kingY - newY) >1){
			notvalid = true;
			return false;
		}
	}
	if(newSquare->getColour()!= nocolour){
				if(holder == newSquare->getColour()){
					notvalid = true;
					return false;		
				}
			}
	if(invalid == false){
		newSquare ->setSquare(currentKing);
		currentKing->setEmpty();
		return true;
	}
	return false;
}
bool Board::movePawn(Square* currentPawn, Square* newSquare){
	int pawnX = currentPawn->getX();
	int pawnY = currentPawn->getY();
	int newX = newSquare->getX();
	int newY = newSquare->getY();
	bool invalid = false;
	Colour holder = currentPawn->getColour();



if(pawnX == 1 || pawnX == 6){ //when pawns are on starting squares, they can move two squares forward
	if(abs(pawnX - newX) > 2){
		notvalid = true;
		return false;
	}
	if(abs(pawnY - newY) > 0){ //diagonal capture movement
		if(newSquare->getColour()== nocolour){
			notvalid = true;
			return false;
		}
		if(newSquare->getColour() != holder) {
			if(abs(newX - pawnX) == 1){
			newSquare->setSquare(currentPawn);
			currentPawn->setEmpty();
			return true;
			}
		}
		notvalid = true;
		return false;
	}
	if(newSquare->getColour() != nocolour){
			notvalid = true;
			return false;
	}
	if(invalid == false){
		newSquare ->setSquare(currentPawn);
		currentPawn->setEmpty();
		notvalid = false;
		return true;
	}
}
else{
	if(holder == white){
	if(pawnX - newX != 1){
		notvalid = true;
		return false;
	}
}
	if(holder == black){
	if(newX - pawnX != 1){
		notvalid = true;
		return false;
	}
}
	if(newSquare->getColour() != holder){
		if(abs(pawnX - newX) >1){
			notvalid = true;
			return false;
		}
		else if(abs(pawnY - newY) >1){
			notvalid = true;
			return false;
		}
		if((abs(pawnX - newX) == 1) && (abs(pawnY - newY) == 1)){ //denotes diagonal capture
			newSquare->setSquare(currentPawn);
			currentPawn->setEmpty();
			return true;
		}
	if(newSquare->getColour() == nocolour){
		if(abs(pawnX-newX) >1){
			notvalid = true;
			return false;
		}
		else if(pawnY != newY){
			notvalid = true;
			return false;
		}
		if(abs(pawnX - newX) == 1){
			newSquare->setSquare(currentPawn);
			currentPawn->setEmpty();
			return true;
		}
	}
	notvalid = true;
	return false;
	}

	if(invalid == false){
		newSquare ->setSquare(currentPawn);
		currentPawn->setEmpty();
		notvalid = false;
		return true;
			}
		}
		return false;
}

bool Board::moveKnight(Square* currentKnight, Square* newSquare){
	int knightX = currentKnight->getX();
	int knightY = currentKnight->getY();
	int newX = newSquare->getX();
	int newY = newSquare-> getY();
	bool invalid = false;
	Square *s;
	Colour holder = currentKnight->getColour();

	if(newX > 7){
		notvalid = true;
		return false;
	}
	if (newY > 7){
		notvalid = true;
		return false;
	}
	if(abs(knightX - newX) == 2 && abs(knightY - newY) == 1){
		if(newSquare->getColour() == nocolour || holder != newSquare->getColour()){
		   newSquare ->setSquare(currentKnight);
		   currentKnight-> setEmpty();
			return true;
		}
	}
	else if(abs(knightY- newY) == 2 && abs(knightX - newX) == 1){
		if(newSquare->getColour() == nocolour || holder != newSquare->getColour()){
		   newSquare ->setSquare(currentKnight);
		   currentKnight-> setEmpty();
			return true;
		}
	}
	notvalid = true;
	return false;
}

bool Board::moveBishop(Square* currentBishop, Square* newSquare) { 
	int bishopX = currentBishop->getX();
	int bishopY = currentBishop->getY();
	int newX = newSquare->getX();
	int newY = newSquare->getY();
	bool invalid = false;
	Square* bishopHolder = currentBishop;
	Square* capturedPiece;
	Colour holder = currentBishop->getColour();

	if(newX > 7){
		notvalid = true;
		return false;
	}
	if(newY > 7){
		notvalid = true;
		return false;
	}

	if (abs(bishopX - newX) == abs(bishopY - newY)) //checks if new coordinates are diagonal from original
	{
		int xIncrement = (newX - bishopX) / (abs(newX - bishopX));
		int yIncrement = (newY - bishopY) / (abs(newY - bishopY));
		
		for (int i = 1; i <= abs(bishopX - newX); i++)
		{
			int xDiagonal = (bishopX + xIncrement*i);
			int yDiagonal = (bishopY + yIncrement*i);
			if (board[xDiagonal][yDiagonal].getColour() == holder){ //returns false if piece is same colour as bishop 
				notvalid = true;
				return false;
			}
				if(board[xDiagonal][yDiagonal].getColour() != nocolour){//checks the diagonal for opposite coloured squares
				capturedPiece = getSquare(xDiagonal,yDiagonal);
				return moveBishop(bishopHolder,capturedPiece);
				}
			}
		newSquare->setSquare(currentBishop); 
		currentBishop->setEmpty();
		return true;
		}
	notvalid = true;
	return false;
}
bool Board::moveRook(Square* currentRook, Square* newSquare){
	int rookX = currentRook->getX();
	int rookY = currentRook->getY();
	int newX = newSquare->getX();
	int newY = newSquare->getY();
	bool invalid = false;
	Colour holder = currentRook->getColour();
	Square* rookHolder = currentRook;
	Square* capturedPiece;

	if(newX == rookX){
		for (int i =rookY - 1; i >= newY; i--){ //make sure i doesnt go past the new Y, out of bounds 
			if(i == newY){
				newSquare->setSquare(currentRook);
				currentRook->setEmpty();
				return false;
				}
			if(board[rookX][i].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[rookX][i].getColour() != nocolour){
				capturedPiece = getSquare(rookX,i);
				return moveQueen(rookHolder,capturedPiece);
			} 
		}
		if(newY > rookY){
			for(int i = rookY + 1; i <= newY; i++){
				if(i == newY){
				newSquare->setSquare(currentRook);
				currentRook->setEmpty();
				return false;
				}
			if(board[rookX][i].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[rookX][i].getColour() != nocolour){
				capturedPiece = getSquare(rookX,i);
				return moveQueen(rookHolder,capturedPiece);
			} 
			}
		}
		if(invalid == true){
			newSquare->setSquare(currentRook);
			currentRook->setEmpty();
		}
		
	}
	if(newY == rookY){
		if(newX < rookX){
		/*if(turn == black){
		for (int i =queenX - 1; i >= newX; i--){ //make sure i doesnt go past the new x, out of bounds 
			if(board[i][queenY].getColour() == holder){
				notvalid = true;
				return false;
			}
			if(i == newX){
				capturedPiece = getSquare(i,queenY);
				return moveQueen(queenHolder,capturedPiece);
			}
		}*/
		//}
		//else if(turn == white){
			for (int i =rookX - 1; i >= newX; i--){ //make sure i doesnt go past the new x, out of bounds
			if(i == newX){
				newSquare->setSquare(currentRook);
				currentRook->setEmpty();
				return false;
				}
			if(board[i][rookY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][rookY].getColour() != nocolour){
				capturedPiece = getSquare(i,rookY);
				return moveQueen(rookHolder,capturedPiece);
			} 
			
		}
		}
		if(newX > rookX){
			if(turn == black){
				for (int i =rookX + 1; i <= newX; i++){ //make sure i doesnt go past the new x, out of bounds 
					if(i == newX){
				newSquare->setSquare(currentRook);
				currentRook->setEmpty();
				return false;
				}
			if(board[i][rookY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][rookY].getColour() != nocolour){
				capturedPiece = getSquare(i,rookY);
				return moveQueen(rookHolder,capturedPiece);
			} 
		}
		}
		else if(turn == white){
			for (int i =rookX + 1; i <= newX; i++){ //make sure i doesnt go past the new x, out of bounds 
				if(i == newX){
				newSquare->setSquare(currentRook);
				currentRook->setEmpty();
				return false;
				}
			if(board[i][rookY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][rookY].getColour() != nocolour){
				capturedPiece = getSquare(i,rookY);
				return moveQueen(rookHolder,capturedPiece);
			} 
			}
		}
		}
		if(invalid == true){
		newSquare->setSquare(currentRook);
		currentRook->setEmpty();
		invalid = false;
		return true;
	}
	}
	notvalid = true;
	return false;
}
bool Board::moveQueen(Square* currentQueen, Square* newSquare){
	int queenX = currentQueen->getX();
	int queenY = currentQueen->getY();
	int newX = newSquare->getX();
	int newY = newSquare->getY();

	Colour holder = currentQueen->getColour();
	bool invalid = false;
	Square* capturedPiece;
	Square* queenHolder = currentQueen;

	if(newX > 7){
		notvalid = true;
		return false;
	}
	if(newY > 7){
		notvalid = true;
		return false;
	}

	if (abs(queenX - newX) == abs(queenY - newY)) //checks if new coordinates are diagonal from original
	{
		int xIncrement = (newX - queenX) / (abs(newX - queenX));
		int yIncrement = (newY - queenY) / (abs(newY - queenY));

		for (int i = 1; i <= abs(queenX - newX); i++)
		{
			int xDiagonal = (queenX + xIncrement*i);
			int yDiagonal = (queenY + yIncrement*i);

			if(newX == i){
				newSquare->setSquare(currentQueen); 
				currentQueen->setEmpty();
				return true;
			}

			if (board[xDiagonal][yDiagonal].getColour() == holder){ //returns false if piece is same colour as queen
				notvalid = true;
				return false;
			}
				if(board[xDiagonal][yDiagonal].getColour() != nocolour){//checks the diagonal for opposite coloured squares
				capturedPiece = getSquare(xDiagonal,yDiagonal);
				return moveQueen(queenHolder,capturedPiece);
				}
			}
		newSquare->setSquare(currentQueen); 
		currentQueen->setEmpty();
		return true;
		
	}
	else if(newX == queenX){
		for (int i =queenY - 1; i >= newY; i--){ //make sure i doesnt go past the new Y, out of bounds 
			if(i == newY){
				newSquare->setSquare(currentQueen);
				currentQueen->setEmpty();
				return false;
				}
			if(board[queenX][i].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[queenX][i].getColour() != nocolour){
				capturedPiece = getSquare(queenX,i);
				return moveQueen(queenHolder,capturedPiece);
			} 
		}
		if(newY > queenY){
			for(int i = queenY + 1; i <= newY; i++){
				if(i == newY){
				newSquare->setSquare(currentQueen);
				currentQueen->setEmpty();
				return false;
				}
			if(board[queenX][i].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[queenX][i].getColour() != nocolour){
				capturedPiece = getSquare(queenX,i);
				return moveQueen(queenHolder,capturedPiece);
			} 
			}
		}
		if(invalid == true){
			newSquare->setSquare(currentQueen);
			currentQueen->setEmpty();
		}
		
	}
	if(newY == queenY){
		if(newX < queenX){
		/*if(turn == black){
		for (int i =queenX - 1; i >= newX; i--){ //make sure i doesnt go past the new x, out of bounds 
			if(board[i][queenY].getColour() == holder){
				notvalid = true;
				return false;
			}
			if(i == newX){
				capturedPiece = getSquare(i,queenY);
				return moveQueen(queenHolder,capturedPiece);
			}
		}*/
		//}
		//else if(turn == white){
			for (int i =queenX - 1; i >= newX; i--){ //make sure i doesnt go past the new x, out of bounds
			if(i == newX){
				newSquare->setSquare(currentQueen);
				currentQueen->setEmpty();
				return false;
				}
			if(board[i][queenY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][queenY].getColour() != nocolour){
				capturedPiece = getSquare(i,queenY);
				return moveQueen(queenHolder,capturedPiece);
			} 
			
		}
		}
		if(newX > queenX){
			if(turn == black){
				for (int i =queenX + 1; i <= newX; i++){ //make sure i doesnt go past the new x, out of bounds 
					if(i == newX){
				newSquare->setSquare(currentQueen);
				currentQueen->setEmpty();
				return false;
				}
			if(board[i][queenY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][queenY].getColour() != nocolour){
				capturedPiece = getSquare(i,queenY);
				return moveQueen(queenHolder,capturedPiece);
			} 
		}
		}
		else if(turn == white){
			for (int i =queenX + 1; i <= newX; i++){ //make sure i doesnt go past the new x, out of bounds 
				if(i == newX){
				newSquare->setSquare(currentQueen);
				currentQueen->setEmpty();
				return false;
				}
			if(board[i][queenY].getColour() == holder){
				notvalid = true;
				return false;
				}
			if(board[i][queenY].getColour() != nocolour){
				capturedPiece = getSquare(i,queenY);
				return moveQueen(queenHolder,capturedPiece);
			} 
			}
		}
		}
		if(invalid == true){
		newSquare->setSquare(currentQueen);
		currentQueen->setEmpty();
		invalid = false;
		return true;
	}
	}
	notvalid = true;
	return false;
}
void Board::printBoard() {
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = board[i][j].getPiece();
			Colour c = board[i][j].getColour();

			switch (p)
			{
			case king: (c == white) ? cout << " K " : cout << " k ";
				break;
			case queen: (c == white) ? cout << " Q " : cout << " q ";
				break;
			case bishop:(c == white) ? cout << " B " : cout << " b ";
				break;
			case knight:(c == white) ? cout << " H " : cout << " h ";
				break;
			case rook: (c == white) ? cout << " R " : cout << " r ";
				break;
			case pawn: (c == white) ? cout << " P " : cout << " p ";
				break;
			//case nocolour:(c != white) ? cout << " " << "empy" << " ";
				//break;
			default: cout << "   ";
				break;
			}

		}
		cout << endl;
	}

}


bool Board::makeMove(int x1, int y1, int x2, int y2){
	using namespace std;
	string move;
	Piece p;
	Square* s;
	Square* t;
	bool invalid = false;

	while (!stopgame)
	{
		(turn == white) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
		cout << "Type in your move as a single four character string. Use x-coordinates first in each pair." << endl;
		cin >> move;
		x1 = move[0] - 48;
		y1 = move[1] - 48;
		x2 = move[2] - 48;
		y2 = move[3] - 48;
		
		s = getSquare(x1,y1);
		t = getSquare(x2,y2);
		s->setX(x1);
		t->setX(x2);
		s->setY(y1);
		t->setY(y2);
		
		if (getSquare(x1, y1)->getColour() == turn){
				p = getSquare(x1,y1)->getPiece();
				switch (p)
			{
			case king: moveKing(s,t);
				break;
			case queen:moveQueen(s,t);
				break;
			case bishop:moveBishop(s,t);
				break;
			case knight:moveKnight(s,t);
				break;
			case rook: moveRook(s,t);
				break;
			case pawn: movePawn(s,t);
				break;
			default: cout << " ";
				break;
			}
			if (notvalid == true){
				cout << "Invalid move, try again." << endl;
				notvalid = false;
				return makeMove(x1,y1,x2,y2);
			}
					if(turn == white){
						turn = black;
						printBoard();
					}
					else {
						turn = white;
						printBoard();
					}
			
		}
		else
			cout << "That's not your piece. Try again." << endl;
	}
	if (getSquare(x2, y2)->getPiece() == king){
		if (getSquare(x1, y1)->getColour() == white)
		{
			cout << "WHITE WINS" << endl;
			return false;
		}
		else{
			cout << "BLACK WINS" << endl;
			return false;
		}
	}
		return false;
}

void Board::setBoard(){
	board[0][0].setPieceAndColor(rook,black);
	board[0][1].setPieceAndColor(knight,black);
	board[0][2].setPieceAndColor(bishop,black);
	board[0][3].setPieceAndColor(queen,black);
	board[0][4].setPieceAndColor(king,black);
	board[0][5].setPieceAndColor(bishop,black);
	board[0][6].setPieceAndColor(knight,black);
	board[0][7].setPieceAndColor(rook,black);
	board[7][0].setPieceAndColor(rook,white);
	board[7][1].setPieceAndColor(knight,white);
	board[7][2].setPieceAndColor(bishop,white);
	board[7][3].setPieceAndColor(queen,white);
	board[7][4].setPieceAndColor(king,white);
	board[7][5].setPieceAndColor(bishop,white);
	board[7][6].setPieceAndColor(knight,white);
	board[7][7].setPieceAndColor(rook,white);


	for(int i = 0; i < 8; i++){
		board[1][i].setPieceAndColor(pawn,black);
		board[6][i].setPieceAndColor(pawn,white);
	}

	for(int i = 2; i < 5; i++){
		for(int j=0; j < 7; j++){
			board[i][j].setPieceAndColor(nopiece,nocolour);
		}
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board[i][j].setX(i);
			board[i][j].setY(j);
		}
	}
	
}
bool Board::playGame()
{
	//system("cls");
	int x1,x2,y1,y2;
	printBoard();
	return makeMove(x1,x2,y1,y2);
	//return doMove();

}





