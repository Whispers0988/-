#include "Memento.h"


Memento::Memento() {}

Memento::Memento(vector<vector<int>> arr, bool turn, deque<PiecePos> lastpieces, int times_B, int times_W)
	: m_turn(turn)
	, m_arr(arr)
	, m_lastPieces(lastpieces)
	, m_times_B(times_B)
	, m_times_W(times_W)
{}