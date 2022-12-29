#ifndef WEIQIMANAGER_H
#define WEIQIMANAGER_H

#include "GameManager.h"
//围棋引擎
class WeiqiGameManager : public GameManager
{
private:
	int breathe;//气
	int count;
	int result[2];

	bool blackXuzhuo = false;
	bool whiteXuzhuo = false;

	std::vector<PiecePos> undoPieces;
public:

	WeiqiGameManager(int road);

	void solve(vector<vector<int>>& arr);
	
	int getBreath(vector<vector<int>>& arr, PiecePos pos, PieceColor color);

	// 函数三：找到arr里面的值为a的数替换为b，并return a的数目
	int change(vector<vector<int>>& arr, int a, int b);

	void deepFirst(vector<vector<int>>& arr, int type, int i, int j);

	bool isPieceBoardFull();

	bool doWork(ActionInfo& actInfo);

	void doXuzhuo(ActionInfo& actInfo);

	bool doLuozi(ActionInfo& actInfo);

	void doFinish(ActionInfo& actInfo);

	bool isLegal(PiecePos pos, PieceColor color);

	void updateUndopieces();

	void updatePieceBoard();

	bool judge(int& winner);
};


#endif