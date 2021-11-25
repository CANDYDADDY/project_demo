#pragma once
#ifndef _GOGANGGAME_H
#define _GOGANGGAME_H

#include"chessboard.h"
#include"chessman.h"
#include<random>
#include<regex>
using namespace std;

class GoGangGame {
public:
	//GoGangGame(const ChessBoard& chsboardd) :chessboard(chsboardd),posX(0),posY(0) {}
	GoGangGame():chessboard(ChessBoard()), posX(0), posY(0) {}
	bool isValid(string inputStr);
	void start();
	bool isReplay(ChessMan);
	bool isWon(int posX, int posY, ChessMan);
	vector<int> computerDo();
private:
	const int WIN_COUNT = 5;
	int posX;
	int posY;
	ChessBoard chessboard;
};
#endif