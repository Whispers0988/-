#ifndef WEIQIMANAGER_H
#define WEIQIMANAGER_H

#include "GameManager.h"
//Χ������
class WeiqiGameManager : public GameManager
{
private:
	int breathe;//��
	int count;
	int result[2];

	bool blackXuzhuo = false;
	bool whiteXuzhuo = false;

	std::vector<PiecePos> undoPieces;
public:

	WeiqiGameManager(int road);

	void solve(vector<vector<int>>& arr);
	
	int getBreath(vector<vector<int>>& arr, PiecePos pos, PieceColor color);

	// ���������ҵ�arr�����ֵΪa�����滻Ϊb����return a����Ŀ
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