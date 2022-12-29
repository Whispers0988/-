#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <windows.h>

#include "PieceBoard.h"
#include "Caretaker.h"
#include "AI.h"

class PieceBoard;
class Caretaker;
class Memento;

//游戏引擎 
class GameManager
{
public:
	GameManager();

	void init(int road);

	~GameManager();

	virtual bool doWork(ActionInfo& actInfo);

	virtual void createAI(int level, int type,int user);

	virtual bool doAIWork(ActionInfo& actInfo);

	virtual bool doLuozi(ActionInfo& actInfo);

	virtual int doHuiqi(bool turn);

	virtual bool doBaocun(bool turn);

	virtual bool doDuru(ActionInfo& info);

	virtual bool doChongkai(ActionInfo& info);

	virtual int getMemNum();

	void drawPieceBoard(int startX, int startY, int width, int height, int padding);
	
	virtual bool judge(int& winner);
	

protected:
	int times_B = 3;     //黑棋剩余悔棋次数（共三次）
	int times_W = 3;     //白棋剩余悔棋次数（共三次）
	PiecePos pos;        //落子位置
	PieceBoard* mPieceboard;
	Caretaker* caretaker;

	HeibaiAI* heibai1 = nullptr;
	HeibaiAI* heibai2 = nullptr;
	WuziAI* wuzi1 = nullptr;
	WuziAI* wuzi2 = nullptr;
};

#endif