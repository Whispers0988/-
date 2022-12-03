#ifndef WUZIQIMANAGER_H
#define WUZIQIMANAGER_H

#include "GameManager.h"

//五子棋引擎
class WuziqiGameManager : public GameManager
{
private:

public:

	WuziqiGameManager(int road) {
		GameManager::init(road);
	}

	bool judge(int& winner) {
		vector<vector<int>> arr = mPieceboard->getArr();
		int m_length = mPieceboard->getLength();
		for (int i = 0; i < m_length; i++) {
			for (int j = 0; j < m_length; j++) {
				//黑棋判断赢了
				if (i + 4 < m_length && (arr[i][j] == 3) && (arr[i + 1][j] == 3) && (arr[i + 2][j] == 3) && (arr[i + 3][j] == 3) && (arr[i + 4][j] == 3))
				{
					winner = 1;
					return true;
				}
				else if (j + 4 < m_length && (arr[i][j] == 3) && (arr[i][j + 1] == 3) && (arr[i][j + 2] == 3) && (arr[i][j + 3] == 3) && (arr[i][j + 4] == 3))
				{
					winner = 1;
					return true;
				}
				else if (i + 4 < m_length && j + 4 < m_length && (arr[i][j] == 3) && (arr[i + 1][j + 1] == 3) && (arr[i + 2][j + 2] == 3) && (arr[i + 3][j + 3] == 3) && (arr[i + 4][j + 4] == 3))
				{
					winner = 1;
					return true;
				}
				else if (i - 4 >= 0 && j + 4 < m_length && (arr[i][j] == 3) && (arr[i - 1][j + 1] == 3) && (arr[i - 2][j + 2] == 3) && (arr[i - 3][j + 3] == 3) && (arr[i - 4][j + 4] == 3))
				{
					winner = 1;
					return true;
				}
				//白棋判断赢了
				if (i + 4 < m_length && (arr[i][j] == 2) && (arr[i + 1][j] == 2) && (arr[i + 2][j] == 2) && (arr[i + 3][j] == 2) && (arr[i + 4][j] == 2))
				{
					winner = 0;
					return true;
				}
				else if (j + 4 < m_length && (arr[i][j] == 2) && (arr[i][j + 1] == 2) && (arr[i][j + 2] == 2) && (arr[i][j + 3] == 2) && (arr[i][j + 4] == 2))
				{
					winner = 0;
					return true;
				}
				else if (i + 4 < m_length && j + 4 < m_length && (arr[i][j] == 2) && (arr[i + 1][j + 1] == 2) && (arr[i + 2][j + 2] == 2) && (arr[i + 3][j + 3] == 2) && (arr[i + 4][j + 4] == 2))
				{
					winner = 0;
					return true;
				}
				else if (i - 4 >= 0 && j + 4 < m_length && (arr[i][j] == 2) && (arr[i - 1][j + 1] == 2) && (arr[i - 2][j + 2] == 2) && (arr[i - 3][j + 3] == 2) && (arr[i - 4][j + 4] == 2))
				{
					winner = 0;
					return true;
				}
			}
		}

		return false;

	}

	bool isPieceBoardFull() {
		auto arr = mPieceboard->getArr();
		for (size_t i = 0; i < mPieceboard->getLength(); i++) {
			for (size_t j = 0; j < mPieceboard->getLength(); j++) {
				if (arr[i][j] == 1) {
					return false;
				}
			}
		}
		return true;
	}

	bool doLuozi(ActionInfo& actInfo) {
		PiecePos pos;

		if (mPieceboard->calcIndex(actInfo.pos.x, actInfo.pos.y, pos)) {
			mPieceboard->record_in(actInfo.color, pos);
			int winner = -1;
			if (judge(winner)) {
				actInfo.finish = true;
				actInfo.winner = winner;
			}
			if (isPieceBoardFull()) {
				actInfo.finish = true;
				actInfo.winner = 2;   //平局记为2
			}
			mPieceboard->draw();

			return true;
		}
		else {
			actInfo.strInfo = L"落子失败\n";
			return false;
		}
	}

};

#endif