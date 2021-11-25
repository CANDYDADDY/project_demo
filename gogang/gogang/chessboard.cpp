#include "chessboard.h"

void ChessBoard::initBoard()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++) {
			m_board[i][j]="+";
		}
	}
}

void ChessBoard::printBoard() const
{
	for (int  i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << m_board[i][j];
		}
		cout << endl;
	}
}

void ChessBoard::setBoard(int posX, int posY, ChessMan chessman)
{
	if (chessman == ChessMan::BLACK) {
		m_board[posX][posY] = "¡ñ";
	}
	else if(chessman == ChessMan::WHITE){
		m_board[posX][posY] = "¡ð";
	}
	
}

vector<vector<string>> ChessBoard::getBoard()
{
	return m_board;
}
