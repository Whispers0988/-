#ifndef COMPONENT_H
#define COMPONENT_H

#include <graphics.h>
#include <memory>
// 带文字的按钮类
class TextButton
{
public:
	TextButton(int x, int y, LPCTSTR str, COLORREF background_color = RGB(255, 205, 150)) :x(x), y(y), str(str), background_color(background_color) {};
	static const int left = 5;
	static const int top = 5;
	static const int roundRadius = 5;
	int x;
	int y;
	LPCTSTR str;
	COLORREF background_color;
	void setX(int _x) {
		x = _x;
	}
	void setY(int _y) {
		y = _y;
	}
	bool isIn(int point_x, int point_y);	// 判断点是否在按钮范围内
	void draw();							// 绘制按钮
};






// 单选框类
class Radio
{
public:
	Radio(int x, int y, int value) :x(x), y(y), value(value) {};
	static const  int radius = 6;
	int x;
	int y;
	int value;
	bool isIn(int point_x, int point_y);	// 判断点是否在单选框范围内
	void draw(int groupValue);				// 绘制单选框
};

#endif