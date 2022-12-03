#ifndef DATAINFO_H
#define DATAINFO_H

#include <iostream>
#include <vector>
#include <deque>
struct Rect {
	int x;
	int y;
	int width;
	int height;
	int padding;
	int space;
	int realLength;

	bool isin(int point_x, int point_y) {
		if (point_x >= x && point_x <= x + width && point_y >= y && point_y <= y + height) {
			return true;
		}
		else {
			return false;
		}
	}
};

//棋的种类
enum Type { WUZIQI, WEIQI };



//棋子颜色  
enum PieceColor { BLACKPIECE, WHITEPIECE };

//下棋指令类型 
enum Action {
	RENFU,
	HUIQI,
	LUOZI,
	XUZHUO,
	BAOCUN,
	DURU,
	CHONGKAI
};

//棋子位置  
struct PiecePos
{
	int x;
	int y;
	PiecePos() {}
	PiecePos(int a, int b) : x(a), y(b) {}
};

//下棋指令信息
struct ActionInfo {
	Action act;
	PiecePos pos;
	PieceColor color;
	bool finish = false;
	int winner = 0;
	bool turn;
	int state;
	//字符串信息
	std::wstring strInfo;
	ActionInfo() {};
	ActionInfo(Action _act, PiecePos _pos, int _state) : act(_act), pos(_pos) {}
};

#endif