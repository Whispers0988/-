

#include "GameManager.h"
#ifndef HEIBAIQIMANAGER_H
#define HEIBAIQIMANAGER_H
//黑白棋引擎
class HeibaiqiGameManager : public GameManager
{
private:
	int result[2]; // 记录当前棋局中黑子、白子个数（result[1]是黑，result[0]是白）

public:

	HeibaiqiGameManager(int road) {
		GameManager::init(road);
		PiecePos pos(mPieceboard->getLength() / 2, mPieceboard->getLength() / 2);
		mPieceboard->record_in(BLACKPIECE, pos);
		mPieceboard->record_in(BLACKPIECE, PiecePos(pos.x + 1, pos.y + 1));
		mPieceboard->record_in(WHITEPIECE, PiecePos(pos.x + 1, pos.y));
		mPieceboard->record_in(WHITEPIECE, PiecePos(pos.x,pos.y+1));
	}

	bool judge(int& winner) {
		vector<vector<int>> arr = mPieceboard->getArr();
		int m_length = mPieceboard->getLength();
		result[0] = result[1] = 0;

		for (size_t i = 0; i < m_length; i++) {
			for (size_t j = 0; j < m_length; j++) {
				if (arr[i][j] == 2) {
					result[0]++;
				}
				else if (arr[i][j] == 3) {
					result[1]++;
				}
			}
		}

		if (result[0] > result[1]) {  // 白棋获胜
			winner = 0;
		}
		else if (result[0] < result[1]) {  //黑棋获胜
			winner = 1;
		}
		else {  // 平局
			winner = 2;
		}
		return true;
	}

	// 判断落子位置是否合法
	bool isLegal(PiecePos pos, PieceColor color) {
		vector<vector<int>> temparr = mPieceboard->getArr();
		
		int count_y = you(pos, color, temparr);
		int count_z = zuo(pos, color, temparr);
		int count_s = shang(pos, color, temparr);
		int count_x = xia(pos, color, temparr);
		int count_ys = youshang(pos, color, temparr);
		int count_yx = youxia(pos, color, temparr);
		int count_zs = zuoshang(pos, color, temparr);
		int count_zx = zuoxia(pos, color, temparr);
		int count = count_y + count_z + count_s + count_x + count_ys + count_yx + count_zs + count_zx;
		
		if (count != 0) {
			return true;
		}
		else {
			return false;
		}
		
	}

	// 判断各个方向，被夹住的子有多少。如果为0，说明该方向上没有被夹住的棋子。
	
	int you(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempy = pos.y + i;

			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int zuo(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempy = pos.y - i;

			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int shang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;

			if (tempx - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int xia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;

			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][pos.y - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;
		}
	}

	int zuoshang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;
			int tempy = pos.y - i;
			if (tempx - 1 < 0) {
				return 0;
			}
			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int youshang(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x - i;
			int tempy = pos.y + i;
			if (tempx - 1 < 0) {
				return 0;
			}
			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int youxia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;
			int tempy = pos.y + i;
			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}

	int zuoxia(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempx = pos.x + i;
			int tempy = pos.y - i;
			if (tempx - 1 == temparr.size()) {
				return 0;
			}
			if (tempy - 1 < 0) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == 1) {  // 如果该方向上遇到空位，不满足夹棋子的条件，返回0
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i == 1) {
				return 0;
			}
			if (temparr[tempx - 1][tempy - 1] == iColor && i > 1) {
				return (i - 1);
			}
			i++;

		}
	}
	

	bool isPieceBoardFull() {  // 棋盘已满 或者 黑白双方均无合法落子位置
		auto arr = mPieceboard->getArr();
		int l = mPieceboard->getLength();
		for (size_t i = 0; i < l; i++) {
			for (size_t j = 0; j < l; j++) {
				if (arr[i][j] == 1) {
					if (isLegal(PiecePos(i + 1, j + 1), WHITEPIECE) || isLegal(PiecePos(i + 1, j + 1), BLACKPIECE)) {
						return false;
					}
				}
			}
		}
		return true;
	}

	bool color_illegal(PieceColor color) {
		auto arr = mPieceboard->getArr();
		for (size_t i = 0; i < mPieceboard->getLength(); i++) {
			for (size_t j = 0; j < mPieceboard->getLength(); j++) {
				if (arr[i][j] == 1) {
					if (isLegal(PiecePos(i + 1, j + 1), color)) {
						return false;
					}
				}
			}
		}
		return true;
	}


	bool doLuozi(ActionInfo& actInfo) {
		PiecePos pos;
		
		if (!color_illegal(actInfo.color)) {  //对应颜色棋子在当前棋盘上有合法落子的位置

			if (mPieceboard->calcIndex(actInfo.pos.x, actInfo.pos.y, pos)) {

				//判断合法性
				if (isLegal(pos, actInfo.color)) {
					mPieceboard->record_in(actInfo.color, pos);

					//被夹住的子，颜色反转
					updatePieceBoard(pos, actInfo.color);
					mPieceboard->draw();

					//判断棋盘是否已满
					if (isPieceBoardFull()) {
						actInfo.finish = true;
						doFinish(actInfo);
					}

					return true;
				}
				else {
					actInfo.strInfo = L"该处不能落子！\n";
					return false;
				}
			}
			else {
				actInfo.strInfo = L"落子失败\n";
				return false;
			}

		}
		else {  //对应颜色棋子在当前棋盘上没有合法落子的位置
			if (actInfo.color == WHITE) {
				actInfo.strInfo = L"白方无子可下，请黑方继续落子\n";
			}
			else {
				actInfo.strInfo = L"黑方无子可下，请白方继续落子\n";
			}
		}

		return true;
	}

	// 将被夹住的棋子，黑白反转
	void updatePieceBoard(PiecePos pos, PieceColor color){
		vector<vector<int>> temparr = mPieceboard->getArr();
		int count_y = you(pos, color, temparr);
		for (int i = 1; i <= count_y; i++) {
			PiecePos temppos;
			temppos.x = pos.x;
			temppos.y = pos.y + i;
			mPieceboard->reversePiece(temppos);
		}
		
		int count_z = zuo(pos, color, temparr);
		for (int i = 1; i <= count_z; i++) {
			PiecePos temppos;
			temppos.x = pos.x;
			temppos.y = pos.y - i;
			mPieceboard->reversePiece(temppos);
		}

		int count_s = shang(pos, color, temparr);
		for (int i = 1; i <= count_s; i++) {
			PiecePos temppos;
			temppos.x = pos.x - i;
			temppos.y = pos.y;
			mPieceboard->reversePiece(temppos);
		}

		int count_x = xia(pos, color, temparr);
		for (int i = 1; i <= count_x; i++) {
			PiecePos temppos;
			temppos.x = pos.x + i;
			temppos.y = pos.y;
			mPieceboard->reversePiece(temppos);
		}

		int count_ys = youshang(pos, color, temparr);
		for (int i = 1; i <= count_ys; i++) {
			PiecePos temppos;
			temppos.x = pos.x - i;
			temppos.y = pos.y + i;
			mPieceboard->reversePiece(temppos);
		}

		int count_yx = youxia(pos, color, temparr);
		for (int i = 1; i <= count_yx; i++) {
			PiecePos temppos;
			temppos.x = pos.x + i;
			temppos.y = pos.y + i;
			mPieceboard->reversePiece(temppos);
		}

		int count_zs = zuoshang(pos, color, temparr);
		for (int i = 1; i <= count_zs; i++) {
			PiecePos temppos;
			temppos.x = pos.x - i;
			temppos.y = pos.y - i;
			mPieceboard->reversePiece(temppos);
		}

		int count_zx = zuoxia(pos, color, temparr);
		for (int i = 1; i <= count_zx; i++) {
			PiecePos temppos;
			temppos.x = pos.x + i;
			temppos.y = pos.y - i;
			mPieceboard->reversePiece(temppos);
		}
	}

	void doFinish(ActionInfo& actInfo) {
		judge(actInfo.winner);
		if (actInfo.winner == 0) {
			actInfo.strInfo += L"\n白棋:" + to_wstring(result[0]) + L"子  黑棋：" + to_wstring(result[1]) + L"子 白棋胜！";
		}
		else if(actInfo.winner == 1){
			actInfo.strInfo += L"\n黑棋:" + to_wstring(result[1]) + L"子  白棋：" + to_wstring(result[0]) + L"子 黑棋胜！";
		}
		else {
			actInfo.strInfo += L"\n黑棋、白棋各：" + to_wstring(result[1]) + L"子  " +  L"   平局";
		}

	}

	bool doAIWork(ActionInfo& actInfo) {
		PiecePos pos;
		if (!color_illegal(actInfo.color)) {
			if (actInfo.color == BLACKPIECE) {
				pos = heibai1->calPos(mPieceboard->getArr(), BLACKPIECE);
			}
			else {
				pos = heibai2->calPos(mPieceboard->getArr(), WHITEPIECE);
			}
			mPieceboard->record_in(actInfo.color, pos);

			//被夹住的子，颜色反转
			updatePieceBoard(pos, actInfo.color);
			Sleep(1000);
			mPieceboard->draw();

			//判断棋盘是否已满
			if (isPieceBoardFull()) {
				actInfo.finish = true;
				doFinish(actInfo);
			}
			return true;
		}
		else {
			return true;
		}
	}

};

#endif
