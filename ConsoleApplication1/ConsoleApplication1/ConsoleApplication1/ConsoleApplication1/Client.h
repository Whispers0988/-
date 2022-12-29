#ifndef CLIENT_H
#define CLIENT_H

#include "component.h"
#include <easyx.h>
#include <graphics.h>
#include "GameFactory.h"
#include "GameManager.h"
#include "UserManager.h"



class Client
{
public:
	enum USERTYPE {
		PLAYER = 0,
		AI,
		TOURIST
	};

	Client(int w, int h);
	
	void init();

	void Start();

	void LoginInit();

	void login();

	bool getIsExit();

	void play();

	void initLayout();

	void drawGame();

	void drawFunc();

	void drawLog();

	void drawPlayClient();

	void setBackGroundColor(COLORREF color);

	void setImgBackGround(LPCTSTR path);

	void loadLog(std::wstring strInfo);

protected:

	bool isInputLegal(wchar_t* s, int& road);

private:
	bool isweiqi;
	bool isExit;
	int width;
	int height;

	int logNum = 0;//能够容纳的日志条数
	int logOffset = 0;
	int index = 0;

	//玩家信息
	USERTYPE player1Type;
	USERTYPE player2Type;

	User* player1 = nullptr;
	User* player2 = nullptr;

	UserManager* um = nullptr;
	int user1Choice = -1;
	int user2Choice = -1;
	
	bool enterGameChoice = false;

	Type gameType;
	int level1 = -1;
	int level2 = -1;

	std::vector<wstring> strLogs;
	std::wstring strLog;

	bool isShowLog = false;

	IMAGE imgBackGround;
	COLORREF colorBackGround;

	TextButton weiqi = TextButton(350, 180, L"围棋");
	TextButton wuziqi = TextButton(330, 280, L"五子棋");
	TextButton heibaiqi = TextButton(330, 380, L"黑白棋");
	TextButton exit = TextButton(315, 480, L"结束游戏");

	TextButton* huiqi;
	TextButton* baocun;
	TextButton* duru;
	TextButton* renfu;
	TextButton* xuzhuo;
	TextButton* restart;

	Radio* Log;

	Radio* login_1;
	Radio* login_2;
	Radio* register_1;
	Radio* register_2;
	Radio* tourist_1;
	Radio* tourist_2;
	Radio* ai_1;
	Radio* ai_2;

	TextButton* submit1;
	TextButton* submit2;
	TextButton* enterGame;

	TextButton* luxiang;
	TextButton* huifang;

	vector<TextButton*> buttons;
	GameManager *gm;

	Rect mGame;
	Rect mFunc;
	Rect mLog;

	int gamePadding = 20;
};

#endif

