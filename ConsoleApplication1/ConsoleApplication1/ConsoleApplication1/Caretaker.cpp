#include "Caretaker.h"


Caretaker::Caretaker() {}

bool Caretaker:: Save(Memento memento)  //保存存档 
{
	m_vecMemento.push_back(memento);
	fstream fs;
	fs.open("save.txt", ios::out);
	if (fs.is_open()) {
		//具体写入文件操作
		//存档个数
		fs << m_vecMemento.size() << endl;

		for (size_t i = 0; i < m_vecMemento.size(); i++) {
			auto mem = m_vecMemento[i];
			fs << i << endl;
			fs << mem.m_turn << endl;

			//队列个数
			fs << mem.m_lastPieces.size() << endl;
			for (const auto& piece : mem.m_lastPieces) {
				fs << piece.x << " " << piece.y << endl;
			}

			//棋盘维数
			fs << mem.m_arr.size() << endl;
			for (size_t j = 0; j < mem.m_arr.size(); j++) {
				for (size_t k = 0; k < mem.m_arr[0].size(); k++) {
					fs << mem.m_arr[j][k] << " ";
				}
				fs << endl;
			}

			//黑棋悔棋次数
			fs << mem.m_times_B << endl;
			//白棋悔棋次数
			fs << mem.m_times_W << endl;
		}
		fs.close();
		return true;
	}
	else {
		return false;
	}
	
}

bool Caretaker:: Load(int state, Memento &mem)     //加载第state个存档 
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
		//具体读取文件操作
		fs >> index;
		for (size_t i = 0; i < index; i++) {
			//读取记录id
			int memIndex = -1;
			fs >> memIndex;
			//读取当前下棋方
			bool turn = false;
			fs >> turn;
			//读取悔棋记录数
			int lastNum = -1;
			fs >> lastNum;
			//读取悔棋记录
			deque<PiecePos> poss;
			for (size_t j = 0; j < lastNum; j++) {
				int x;
				int y;
				fs >> x >> y;
				poss.push_back(PiecePos(x, y));
			}
			//棋盘维数
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

			//悔棋信息
			int black_info;
			fs >> black_info;
			int white_info;
			fs >> white_info;

			m_vecMemento.push_back(Memento(arrPieceBoard, turn, poss, black_info, white_info));
		}
		fs.close();
	}
	
}