#ifndef MEMENTO_H
#define MEMENTO_H

#include "DataInfo.h"

using namespace std;

//����¼�� (���ڱ��浱ǰ������Ϣ)
class Memento
{
public:
	vector<vector<int>> m_arr;
	bool m_turn;   //�ֵ���һ��������Ϣ
	deque<PiecePos> m_lastPieces; //���ڻ������Ϣ
	int m_times_B;//����������
	int m_times_W;//����������

public:
	Memento();

	Memento(vector<vector<int>> arr, bool turn, deque<PiecePos> lastpieces, int times_B, int times_W);

};

#endif