#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "PieceBoard.h"
#include "Caretaker.h"

class PieceBoard;
class Caretaker;
class Memento;

//��Ϸ���� 
class GameManager
{
public:
	GameManager();

	void init(int road);

	~GameManager();

	virtual bool doWork(ActionInfo& actInfo);

	virtual bool doLuozi(ActionInfo& actInfo);

	virtual int doHuiqi(bool turn);

	virtual bool doBaocun(bool turn);

	virtual bool doDuru(ActionInfo& info);

	virtual bool doChongkai(ActionInfo& info);

	virtual int getMemNum();

	void drawPieceBoard(int startX, int startY, int width, int height, int padding);
	
	virtual bool judge(int& winner);
	

protected:
	int times_B = 3;     //����ʣ���������������Σ�
	int times_W = 3;     //����ʣ���������������Σ�
	PiecePos pos;        //����λ��
	PieceBoard* mPieceboard;
	Caretaker* caretaker;
};

#endif