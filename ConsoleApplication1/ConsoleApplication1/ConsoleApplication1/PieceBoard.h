#ifndef PIECEBOARD_H
#define PIECEBOARD_H

#include "Memento.h"
#include <graphics.h>


class Memento;

//棋盘
class PieceBoard
{
public:
	//过去的棋子位置记录
	deque<PiecePos> lastPieces;
private:
	
	int queueMax = 12;

	vector<PiecePos> m_vecPos; //存放棋子的位置  
	int m_Length = 9;

	Rect *mBoard = nullptr;
	// 用于记录棋局
	vector<vector<int>> arr = vector<vector<int>>(m_Length, vector<int>(m_Length));
	IMAGE img;
	
public:
	PieceBoard() ;
	PieceBoard(int road);
	~PieceBoard();

	void setLength(int length);

	//对棋子队列的处理
	void addPiece(PiecePos pos);

	int getLength();

	vector<vector<int>> getArr();

	void setArr(vector<vector<int>> newarr);

	//将鼠标坐标转换为棋盘矩阵消息
	bool calcIndex(int point_x, int point_y, PiecePos& pos);

	void updatePieceBoard();

	void initBoard(int startX, int startY, int width, int height, int padding);

	void draw();

	void clearPieceBoard();

	void SetPiece(PieceColor color, PiecePos pos);

	//将棋子记录到棋盘中
	bool record_in(PieceColor color, PiecePos pos);

	//清空棋子
	void clearPieces();

	void clearDeque();

	//将指定棋子取走（用于悔棋和提子）
	void undoPiece(PiecePos pos);

	//保存棋局，只与Memento对象交互，不涉及到caretaker
	Memento Save(bool turn, int times_B, int times_W);
	
	//载入棋局，只与Memento对象交互，不涉及到caretaker
	void Load(Memento memento);
	
};


#endif