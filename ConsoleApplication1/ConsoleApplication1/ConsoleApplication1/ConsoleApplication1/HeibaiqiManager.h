

#include "GameManager.h"
#ifndef HEIBAIQIMANAGER_H
#define HEIBAIQIMANAGER_H
//�ڰ�������
class HeibaiqiGameManager : public GameManager
{
private:
	int result[2]; // ��¼��ǰ����к��ӡ����Ӹ�����result[1]�Ǻڣ�result[0]�ǰף�

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

		if (result[0] > result[1]) {  // �����ʤ
			winner = 0;
		}
		else if (result[0] < result[1]) {  //�����ʤ
			winner = 1;
		}
		else {  // ƽ��
			winner = 2;
		}
		return true;
	}

	// �ж�����λ���Ƿ�Ϸ�
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

	// �жϸ������򣬱���ס�����ж��١����Ϊ0��˵���÷�����û�б���ס�����ӡ�
	
	int you(PiecePos pos, PieceColor color, vector<vector<int>> temparr) {
		int i = 1;
		int iColor = (color == BLACKPIECE) ? 3 : 2;
		while (1) {
			int tempy = pos.y + i;

			if (tempy - 1 == temparr.size()) {
				return 0;
			}
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[pos.x - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][pos.y - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
			if (temparr[tempx - 1][tempy - 1] == 1) {  // ����÷�����������λ������������ӵ�����������0
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
	

	bool isPieceBoardFull() {  // �������� ���� �ڰ�˫�����޺Ϸ�����λ��
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
		
		if (!color_illegal(actInfo.color)) {  //��Ӧ��ɫ�����ڵ�ǰ�������кϷ����ӵ�λ��

			if (mPieceboard->calcIndex(actInfo.pos.x, actInfo.pos.y, pos)) {

				//�жϺϷ���
				if (isLegal(pos, actInfo.color)) {
					mPieceboard->record_in(actInfo.color, pos);

					//����ס���ӣ���ɫ��ת
					updatePieceBoard(pos, actInfo.color);
					mPieceboard->draw();

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
		else {  //��Ӧ��ɫ�����ڵ�ǰ������û�кϷ����ӵ�λ��
			if (actInfo.color == WHITE) {
				actInfo.strInfo = L"�׷����ӿ��£���ڷ���������\n";
			}
			else {
				actInfo.strInfo = L"�ڷ����ӿ��£���׷���������\n";
			}
		}

		return true;
	}

	// ������ס�����ӣ��ڰ׷�ת
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
			actInfo.strInfo += L"\n����:" + to_wstring(result[0]) + L"��  ���壺" + to_wstring(result[1]) + L"�� ����ʤ��";
		}
		else if(actInfo.winner == 1){
			actInfo.strInfo += L"\n����:" + to_wstring(result[1]) + L"��  ���壺" + to_wstring(result[0]) + L"�� ����ʤ��";
		}
		else {
			actInfo.strInfo += L"\n���塢�������" + to_wstring(result[1]) + L"��  " +  L"   ƽ��";
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

			//����ס���ӣ���ɫ��ת
			updatePieceBoard(pos, actInfo.color);
			Sleep(1000);
			mPieceboard->draw();

			//�ж������Ƿ�����
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
