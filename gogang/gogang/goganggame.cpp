#include"goganggame.h"


bool GoGangGame::isValid(string inputStr)
{
	vector<string> posStrArr;
	//正则表达式，字符串分割
	regex re(",");
	sregex_token_iterator p(inputStr.begin(), inputStr.end(), re, -1);
	sregex_token_iterator end;
	while (p != end)
		posStrArr.push_back(*p++);
	try {
		posX = atoi(posStrArr.at(0).c_str()) - 1;//使用下标运算符，不会抛出异常
		posY = atoi(posStrArr.at(1).c_str()) - 1;
	}
	catch(const exception& e){
		chessboard.printBoard();
		cout << "请以（数字，数字）的格式输入： ";
		return false;
	}
	if (posX < 0 || posX >= ChessBoard::BOARD_SIZE || posY < 0 || posY >= ChessBoard::BOARD_SIZE) {
		chessboard.printBoard();
		cout<<"X与Y坐标输入错误，请重新输入：";
		return false;
	}
	vector<vector<string>> board = chessboard.getBoard();
	if (board[posX][posY] != "+") {
		chessboard.printBoard();
		cout<<"此位置已经有棋子，请重新输入： ";
		return false;
	}
	return true;
}

void GoGangGame::start()
{
	bool isOver = false;
//	chessboard.initBoard();
	chessboard.printBoard();
	cout << "请输入您下棋的坐标，应以x,y的格式输入： ";
	string inputStr("");
	while (cin>>inputStr) {
		isOver = false;
		if (!isValid(inputStr))
			continue;
		ChessMan chessman = ChessMan::BLACK;
		chessboard.setBoard(posX, posY, ChessMan::BLACK);
		if (isWon(posX, posY, chessman))
			isOver = true;
		else {
			vector<int> computerPosArr = computerDo();
			chessman = ChessMan::WHITE;
			chessboard.setBoard(computerPosArr[0], computerPosArr[1], chessman);
			if (isWon(computerPosArr[0], computerPosArr[1], chessman))
				isOver = true;

		}
		if (isOver) {
			if (isReplay(chessman)) {
				chessboard.initBoard();
				chessboard.printBoard();
				continue;
			}
			break;
		}
		chessboard.printBoard();
		cout<<"请输入您下棋的坐标，应以x,y的格式输入： ";
	}
}

bool GoGangGame::isReplay(ChessMan chessman)
{
	chessboard.printBoard();
	if (chessman == ChessMan::BLACK) {
		cout << "恭喜你，您赢了,再下一局？（y/n）" << endl;
	}
	else {
		cout << "很遗憾，您输了, 再下一局？（y/n）" << endl;
	}
	char ch;
	cin >> ch;
	if (ch == 'y')
		return true;
	return false;
}

bool GoGangGame::isWon(int posX, int posY, ChessMan ico)
{
	int startX = 0;
	int startY = 0;
	int endX = chessboard.BOARD_SIZE - 1;
	int endY = endX;
	int sameCount1 = 0;
	int sameCount2 = 0;
	int sameCount3 = 0;
	int sameCount4 = 0;
	int tmp = 0;
	tmp = posX - WIN_COUNT + 1;
	startX = tmp < 0 ? 0 : tmp;
	tmp = posY - WIN_COUNT + 1;
	startY = tmp < 0 ? 0 : tmp;
	tmp = posX + WIN_COUNT - 1;
	endX = tmp > chessboard.BOARD_SIZE - 1 ? chessboard.BOARD_SIZE - 1 : tmp;
	tmp = posY + WIN_COUNT - 1;
	endY = tmp > chessboard.BOARD_SIZE - 1 ? chessboard.BOARD_SIZE - 1 : tmp;
	vector<vector<string>> board = chessboard.getBoard();
	string icostr= (ico == ChessMan::BLACK)?"●":"○";
	for (int i = startY; i < endY; i++) {
		if (board[posX][i] == icostr && board[posX][i + 1] == icostr) {
			sameCount1++;
		}
		else if (sameCount1 != WIN_COUNT - 1) {
			sameCount1 = 0;
		}
	}
	for (int i = startX; i < endX; i++) {
		if (board[i][posY] == icostr && board[i + 1][posY] == icostr) {
			sameCount2++;
		}
		else if (sameCount2 != WIN_COUNT - 1) {
			sameCount2 = 0;
		}
	}
	for (int i = startX, j = startY; i < endX && j < endY; i++, j++) {
		if (board[i][j] == icostr && board[i + 1][j + 1] == icostr) {
			sameCount3++;
		}
		else if (sameCount3 != WIN_COUNT - 1) {
			sameCount3 = 0;
		}
	}
	for (int i = endX, j = startY; i > startX && j < endY; i--, j++) {
		if (board[i][j] == icostr && board[i - 1][j + 1] == icostr) {
			sameCount4++;
		}
		else if (sameCount4 != WIN_COUNT - 1) {
			sameCount4 = 0;
		}
	}

	if (sameCount1 >= WIN_COUNT - 1 || sameCount2 >= WIN_COUNT - 1 || sameCount3 >= WIN_COUNT - 1
		|| sameCount4 >= WIN_COUNT - 1)
		return true;
	else {
		return false;
	}
}

vector<int> GoGangGame::computerDo()
{
	//使用随机数
	random_device e;
	uniform_real_distribution<double> u(0, 1);
	int posx = (int)(u(e) * chessboard.BOARD_SIZE);
	int posy = (int)(u(e) * chessboard.BOARD_SIZE);
	vector<vector<string>> board = chessboard.getBoard();
	while (board[posx][posy] != "+") {
		posx = (int)(u(e) * chessboard.BOARD_SIZE);
		posy = (int)(u(e) * chessboard.BOARD_SIZE);
	}
	return vector<int>{posx, posy};
}
