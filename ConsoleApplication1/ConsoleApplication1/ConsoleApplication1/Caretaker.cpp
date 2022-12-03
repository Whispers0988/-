#include "Caretaker.h"


Caretaker::Caretaker() {}

bool Caretaker:: Save(Memento memento)  //����浵 
{
	m_vecMemento.push_back(memento);
	fstream fs;
	fs.open("save.txt", ios::out);
	if (fs.is_open()) {
		//����д���ļ�����
		//�浵����
		fs << m_vecMemento.size() << endl;

		for (size_t i = 0; i < m_vecMemento.size(); i++) {
			auto mem = m_vecMemento[i];
			fs << i << endl;
			fs << mem.m_turn << endl;

			//���и���
			fs << mem.m_lastPieces.size() << endl;
			for (const auto& piece : mem.m_lastPieces) {
				fs << piece.x << " " << piece.y << endl;
			}

			//����ά��
			fs << mem.m_arr.size() << endl;
			for (size_t j = 0; j < mem.m_arr.size(); j++) {
				for (size_t k = 0; k < mem.m_arr[0].size(); k++) {
					fs << mem.m_arr[j][k] << " ";
				}
				fs << endl;
			}

			//����������
			fs << mem.m_times_B << endl;
			//����������
			fs << mem.m_times_W << endl;
		}
		fs.close();
		return true;
	}
	else {
		return false;
	}
	
}

bool Caretaker:: Load(int state, Memento &mem)     //���ص�state���浵 
{
	if (m_vecMemento.size() <= state) {
		return false;
	}
	else {
		mem = m_vecMemento[state];
		return true;
	}

}

void Caretaker::Init() {
	fstream fs;
	fs.open("save.txt", ios::in);
	if (fs.is_open()) {
		//�����ȡ�ļ�����
		fs >> index;
		for (size_t i = 0; i < index; i++) {
			//��ȡ��¼id
			int memIndex = -1;
			fs >> memIndex;
			//��ȡ��ǰ���巽
			bool turn = false;
			fs >> turn;
			//��ȡ�����¼��
			int lastNum = -1;
			fs >> lastNum;
			//��ȡ�����¼
			deque<PiecePos> poss;
			for (size_t j = 0; j < lastNum; j++) {
				int x;
				int y;
				fs >> x >> y;
				poss.push_back(PiecePos(x, y));
			}
			//����ά��
			int length = -1;
			fs >> length;
			vector<vector<int>> arrPieceBoard;
			
			for (size_t j = 0; j < length; j++) {
				vector<int> row;
				for (size_t k = 0; k < length; k++) {
					int temp = -1;
					fs >> temp;
					row.push_back(temp);
				}
				arrPieceBoard.push_back(row);
			}

			//������Ϣ
			int black_info;
			fs >> black_info;
			int white_info;
			fs >> white_info;

			m_vecMemento.push_back(Memento(arrPieceBoard, turn, poss, black_info, white_info));
		}
		fs.close();
	}
	
}