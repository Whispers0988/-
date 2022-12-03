#ifndef MEMENTO_H
#define MEMENTO_H

#include "DataInfo.h"

using namespace std;

//备忘录类 (用于保存当前棋盘信息)
class Memento
{
public:
	vector<vector<int>> m_arr;
	bool m_turn;   //轮到哪一方下棋信息
	deque<PiecePos> m_lastPieces; //用于悔棋的信息
	int m_times_B;//黑棋悔棋次数
	int m_times_W;//白棋悔棋次数

public:
	Memento();

	Memento(vector<vector<int>> arr, bool turn, deque<PiecePos> lastpieces, int times_B, int times_W);

};

#endif