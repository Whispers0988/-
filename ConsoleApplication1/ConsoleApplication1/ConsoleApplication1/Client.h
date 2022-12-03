#ifndef CLIENT_H
#define CLIENT_H

#include "component.h"
#include <easyx.h>
#include <graphics.h>
#include "GameFactory.h"
#include "GameManager.h"




class Client
{
public:
	Client(int w, int h);
	
	void init();

	void Start();

	bool getIsExit();

	void play();

	void initLayout();

	void drawGame();

	void drawFunc();

	void drawLog();

	void drawPlayClient();

	void setBackGroundColor(COLORREF color);

	void setImgBackGround(LPCTSTR path);


protected:

	bool isInputLegal(wchar_t* s, int& road);

private:
	bool isweiqi;
	bool isExit;
	int width;
	int height;

	int logNum = 0;//�ܹ����ɵ���־����
	int logOffset = 0;
	int index = 0;

	std::vector<wstring> strLogs;
	std::wstring strLog;

	bool isShowLog = false;

	IMAGE imgBackGround;
	COLORREF colorBackGround;

	TextButton weiqi = TextButton(350, 200, L"Χ��");
	TextButton wuziqi = TextButton(330, 300, L"������");
	TextButton exit = TextButton(320, 400, L"������Ϸ");

	TextButton* huiqi;
	TextButton* baocun;
	TextButton* duru;
	TextButton* renfu;
	TextButton* xuzhuo;
	TextButton* restart;

	Radio* Log;

	vector<TextButton*> buttons;
	GameManager *gm;

	Rect mGame;
	Rect mFunc;
	Rect mLog;

	int gamePadding = 20;
};

#endif

