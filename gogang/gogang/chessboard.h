#pragma once
#ifndef _CHESSBOARD_H
#define _CHESSBOARD_H

#include<string>
#include<vector>
#include<iostream>
#include"chessman.h"
using namespace std;


class ChessBoard {
public:
	ChessBoard() :m_board(BOARD_SIZE,vector<string>(BOARD_SIZE,"+")) {}	
	void initBoard();
	void printBoard()const;
	void setBoard(int, int, ChessMan);
	vector<vector<string>> getBoard();
public:
	const static int BOARD_SIZE = 22;
private:
	vector<vector<string>> m_board;
};
#endif