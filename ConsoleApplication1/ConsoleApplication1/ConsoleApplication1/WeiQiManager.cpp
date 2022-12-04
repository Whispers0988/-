#include "WeiQiManager.h"

WeiqiGameManager::WeiqiGameManager(int road) {
	GameManager::init(road);
}

void WeiqiGameManager::solve(vector<vector<int>>& arr) {
	breathe = 0;
	count = 0;
	result[0] = 0;  // ����ӽ��
	result[1] = 0;

	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			// �������Ѿ���������ӺͿա�����0�����������1����Ϊ����
			if (arr[i][j] == 0 || arr[i][j] == 1) continue;
			// ���������ӣ��ҵ�������֮�������ӡ���
			if (arr[i][j] == 2) {
				deepFirst(arr, 2, i, j);
				breathe = change(arr, -1, 1); // ����
				if (breathe >= 2) {
					result[0] += count;
				}

				breathe = 0;    // ����
				count = 0;
			}

			// ���������ӣ��ҵ�������֮�������ӡ���
			if (arr[i][j] == 3) {
				deepFirst(arr, 3, i, j);
				breathe = change(arr, -1, 1); // ����
				if (breathe >= 2) {
					result[1] += count;
				}

				breathe = 0;    // ����
				count = 0;
			}
		}
	}
}

int WeiqiGameManager::getBreath(vector<vector<int>>& arr, PiecePos pos, PieceColor color) {
	// ����Խ��
	if (pos.x < 0 || pos.x >= arr.size() || pos.y < 0 || pos.y >= arr[0].size()) {
		return 0;
	}
	//�Ѿ���������
	if (arr[pos.x][pos.y] == 0) {
		return 0;
	}
	//����˴�����
	if (arr[pos.x][pos.y] == 1) {
		arr[pos.x][pos.y] = 0;
		return 1;
	}
	//�˴��ǰ���
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
	//�˴��Ǻ���
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


// �ҵ�arr�����ֵΪa�����滻Ϊb����return a����Ŀ
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

	// ����Խ��
	if (i < 0 || i >= arr.size() || j < 0 || j >= arr[0].size())  return;
	// ����Ϊ1����
	if (arr[i][j] == 1) {
		arr[i][j] = -1;
		return;
	}// ���Ӳ�ƥ��
	else if (arr[i][j] != type) {
		return;
	}
	// ����Ϊ��������
	count++;
	arr[i][j] = 0;

	// �ݹ�
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
		//��������
		whiteXuzhuo = true;
		actInfo.strInfo = L"�������ţ�";
	}
	else {
		blackXuzhuo = true;
		actInfo.strInfo = L"�������ţ�";
	}

	if (whiteXuzhuo && blackXuzhuo) {
		actInfo.finish = true;
		doFinish(actInfo);
	}
}

bool WeiqiGameManager::doLuozi(ActionInfo& actInfo) {
	PiecePos pos;

	if (mPieceboard->calcIndex(actInfo.pos.x, actInfo.pos.y, pos)) {

		//�жϺϷ���
		if (isLegal(pos, actInfo.color)) {
			mPieceboard->record_in(actInfo.color, pos);
			//���£�����������
			updatePieceBoard();
			mPieceboard->draw();
			if (actInfo.color == WHITEPIECE) {
				whiteXuzhuo = false;
			}
			else {
				blackXuzhuo = false;
			}

			//�ж������Ƿ�����
			if (isPieceBoardFull()) {
				actInfo.finish = true;
				doFinish(actInfo);
			}

			return true;
		}
		else {
			actInfo.strInfo = L"�ô��������ӣ�\n";
			return false;
		}
	}
	else {
		actInfo.strInfo = L"����ʧ��\n";
		return false;
	}
}

void WeiqiGameManager::doFinish(ActionInfo& actInfo) {
	judge(actInfo.winner);
	if (actInfo.winner == 0) {
		actInfo.strInfo += L"\n����:" + to_wstring(result[0]) + L"��  ���壺" + to_wstring(result[1]) + L"�� ����ʤ��";
	}
	else {
		actInfo.strInfo += L"\n����:" + to_wstring(result[1]) + L"��  ���壺" + to_wstring(result[0]) + L"�� ����ʤ��";
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
				//����
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