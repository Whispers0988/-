#include "WeiQiManager.h"

WeiqiGameManager::WeiqiGameManager(int road) {
	GameManager::init(road);
}

void WeiqiGameManager::solve(vector<vector<int>>& arr) {
	breathe = 0;
	count = 0;
	result[0] = 0;  // 活白子结果
	result[1] = 0;

	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			// 遍历到已经处理过的子和空。矩阵0代表遍历过，1代表为无子
			if (arr[i][j] == 0 || arr[i][j] == 1) continue;
			// 遍历到白子，找到所有与之相连的子、气
			if (arr[i][j] == 2) {
				deepFirst(arr, 2, i, j);
				breathe = change(arr, -1, 1); // 回溯
				if (breathe >= 2) {
					result[0] += count;
				}

				breathe = 0;    // 回溯
				count = 0;
			}

			// 遍历到黑子，找到所有与之相连的子、气
			if (arr[i][j] == 3) {
				deepFirst(arr, 3, i, j);
				breathe = change(arr, -1, 1); // 回溯
				if (breathe >= 2) {
					result[1] += count;
				}

				breathe = 0;    // 回溯
				count = 0;
			}
		}
	}
}

int WeiqiGameManager::getBreath(vector<vector<int>>& arr, PiecePos pos, PieceColor color) {
	// 该子越界
	if (pos.x < 0 || pos.x >= arr.size() || pos.y < 0 || pos.y >= arr[0].size()) {
		return 0;
	}
	//已经遍历过的
	if (arr[pos.x][pos.y] == 0) {
		return 0;
	}
	//如果此处无子
	if (arr[pos.x][pos.y] == 1) {
		arr[pos.x][pos.y] = 0;
		return 1;
	}
	//此处是白子
	else if (arr[pos.x][pos.y] == 2) {
		if (color == BLACKPIECE) {
			arr[pos.x][pos.y] = 0;
			return 0;
		}
		else {
			arr[pos.x][pos.y] = 0;
			int up = getBreath(arr, PiecePos(pos.x - 1, pos.y), WHITEPIECE);
			int left = getBreath(arr, PiecePos(pos.x, pos.y - 1), WHITEPIECE);
			int right = getBreath(arr, PiecePos(pos.x, pos.y + 1), WHITEPIECE);
			int down = getBreath(arr, PiecePos(pos.x + 1, pos.y), WHITEPIECE);
			return up + left + right + down;
		}
	}
	//此处是黑子
	else {
		if (color == WHITEPIECE) {
			arr[pos.x][pos.y] = 0;
			return 0;
		}
		else {
			arr[pos.x][pos.y] = 0;
			int up = getBreath(arr, PiecePos(pos.x - 1, pos.y), BLACKPIECE);
			int left = getBreath(arr, PiecePos(pos.x, pos.y - 1), BLACKPIECE);
			int right = getBreath(arr, PiecePos(pos.x, pos.y + 1), BLACKPIECE);
			int down = getBreath(arr, PiecePos(pos.x + 1, pos.y), BLACKPIECE);
			return up + left + right + down;
		}
	}
}


// 找到arr里面的值为a的数替换为b，并return a的数目
int WeiqiGameManager::change(vector<vector<int>>& arr, int a, int b) {
	int changeNum = 0;
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] == a) {
				arr[i][j] = b;
				changeNum++;
			}
		}
	}
	return changeNum;
}
void WeiqiGameManager::deepFirst(vector<vector<int>>& arr, int type, int i, int j) {

	// 该子越界
	if (i < 0 || i >= arr.size() || j < 0 || j >= arr[0].size())  return;
	// 该子为1，空
	if (arr[i][j] == 1) {
		arr[i][j] = -1;
		return;
	}// 该子不匹配
	else if (arr[i][j] != type) {
		return;
	}
	// 该子为相连的子
	count++;
	arr[i][j] = 0;

	// 递归
	deepFirst(arr, type, i + 1, j);
	deepFirst(arr, type, i - 1, j);
	deepFirst(arr, type, i, j + 1);
	deepFirst(arr, type, i, j - 1);
}

bool WeiqiGameManager::isPieceBoardFull() {
	auto arr = mPieceboard->getArr();
	for (size_t i = 0; i < mPieceboard->getLength(); i++) {
		for (size_t j = 0; j < mPieceboard->getLength(); j++) {
			if (arr[i][j] == 1) {
				if (isLegal(PiecePos(i + 1, j + 1), WHITEPIECE) || isLegal(PiecePos(i + 1, j + 1), BLACKPIECE)) {
					return false;
				}
			}
		}
	}
	return true;
}

bool WeiqiGameManager::doWork(ActionInfo& actInfo) {
	if (actInfo.act != XUZHUO) {
		return GameManager::doWork(actInfo);
	}
	else {
		doXuzhuo(actInfo);
		return true;
	}
}

void WeiqiGameManager::doXuzhuo(ActionInfo& actInfo) {
	if (actInfo.turn) {
		//白棋虚着
		whiteXuzhuo = true;
		actInfo.strInfo = L"白棋虚着！";
	}
	else {
		blackXuzhuo = true;
		actInfo.strInfo = L"黑棋虚着！";
	}

	if (whiteXuzhuo && blackXuzhuo) {
		actInfo.finish = true;
		doFinish(actInfo);
	}
}

bool WeiqiGameManager::doLuozi(ActionInfo& actInfo) {
	PiecePos pos;

	if (mPieceboard->calcIndex(actInfo.pos.x, actInfo.pos.y, pos)) {

		//判断合法性
		if (isLegal(pos, actInfo.color)) {
			mPieceboard->record_in(actInfo.color, pos);
			//更新，把死子提走
			updatePieceBoard();
			mPieceboard->draw();
			if (actInfo.color == WHITEPIECE) {
				whiteXuzhuo = false;
			}
			else {
				blackXuzhuo = false;
			}

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

void WeiqiGameManager::doFinish(ActionInfo& actInfo) {
	judge(actInfo.winner);
	if (actInfo.winner == 0) {
		actInfo.strInfo += L"\n白棋:" + to_wstring(result[0]) + L"子  黑棋：" + to_wstring(result[1]) + L"子 白棋胜！";
	}
	else {
		actInfo.strInfo += L"\n黑棋:" + to_wstring(result[1]) + L"子  白棋：" + to_wstring(result[0]) + L"子 黑棋胜！";
	}
}

bool WeiqiGameManager::isLegal(PiecePos pos, PieceColor color) {
	vector<vector<int>> temparr = mPieceboard->getArr();

	if (color == WHITEPIECE) {
		temparr[pos.x - 1][pos.y - 1] = 2;
	}
	else {
		temparr[pos.x - 1][pos.y - 1] = 3;
	}

	int breath = getBreath(temparr, PiecePos(pos.x - 1, pos.y - 1), color);

	if (breath <= 0) {
		return false;
	}
	else {
		return true;
	}
}

void WeiqiGameManager::updateUndopieces() {
	undoPieces.clear();
	for (size_t i = 0; i < mPieceboard->getLength(); i++) {
		for (size_t j = 0; j < mPieceboard->getLength(); j++) {
			vector<vector<int>> temparr = mPieceboard->getArr();
			PiecePos pos(i, j);
			int res = -1;
			if (temparr[i][j] == 2) {
				//白棋
				res = getBreath(temparr, pos, WHITEPIECE);
			}
			else if (temparr[i][j] == 3) {
				res = getBreath(temparr, pos, BLACKPIECE);
			}
			if (res == 0) {
				undoPieces.push_back(pos);
			}
		}
	}
}

void WeiqiGameManager::updatePieceBoard() {
	updateUndopieces();
	for (auto& piece : undoPieces) {
		mPieceboard->undoPiece(piece);
	}
}

bool WeiqiGameManager::judge(int& winner) {

	auto arr = mPieceboard->getArr();
	solve(arr);

	if (result[1] - 3.75 > result[0]) {
		winner = 1;
	}
	else {
		winner = 0;
	}

	return true;
}