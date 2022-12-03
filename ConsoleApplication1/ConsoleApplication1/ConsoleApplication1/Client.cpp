#include "Client.h"


Client::Client(int w, int h) :width(w), height(h) {
	isExit = true;
}
void Client::init() {
	HWND hwnd = initgraph(width, height);
	setImgBackGround(L"back.jpg");

	setbkcolor(colorBackGround);
	cleardevice();
	loadimage(&imgBackGround, L"back.jpg", width, height);
	putimage(0, 0, &imgBackGround);
	SetWindowText(hwnd, L"棋类对战平台");
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, L"楷体");
	settextcolor(BLACK);
	outtextxy(180, 40, L"棋类对战平台");
	wchar_t s[10];


	settextstyle(40, 0, L"楷体");
	weiqi.draw();
	wuziqi.draw();
	exit.draw();
}

void Client::Start() {
	while (1) {
		ExMessage msg;
		getmessage(&msg, EM_MOUSE);
		wchar_t s[10];
		if (msg.lbutton) {
			if (weiqi.isIn(msg.x, msg.y)) {
				InputBox(s, 10, L"请输入围棋棋盘大小，可以选择8~19");
				int road = -1;
				if (isInputLegal(s, road)) {
					Type type = WEIQI;
					GameFactory fc;
					gm = fc.createGameManager(type, road);
					isweiqi = true;
					break;
				}
			}
			else if (wuziqi.isIn(msg.x, msg.y)) {
				InputBox(s, 10, L"请输入五子棋棋盘大小，可以选择8~19");
				int road = -1;
				if (isInputLegal(s, road)) {
					Type type = WUZIQI;
					GameFactory fc;
					gm = fc.createGameManager(type, road);
					isweiqi = false;
					break;
				}
				else {
					MessageBox(GetHWnd(), L"您输入的棋盘大小有误！游戏创建失败！", L"错误", 0);
					flushmessage(EM_MOUSE);
					continue;
				}
			}
			else if (exit.isIn(msg.x, msg.y)) {
				closegraph();
				break;
			}
			flushmessage(EM_MOUSE);
		}
	}
}
bool Client::getIsExit() {
	return isExit;
}

void Client::play() {
	drawPlayClient();
	int count = 0;
	int LogValue = 0;
	bool turn = false;//黑棋先手
	int oldx = -1;
	int oldy = -1;

	while (1) {
		ActionInfo info;
		ExMessage msg;
		flushmessage(EM_MOUSE);
		getmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			if (oldx == msg.x && oldy == msg.y) {
				continue;
			}
			else {
				oldx = msg.x;
				oldy = msg.y;
			}

			if (Log->isIn(msg.x, msg.y)) {
				if (LogValue == 1) {
					LogValue = 0;
					clearcircle(Log->x, Log->y, Log->radius);
					Log->draw(LogValue);
					isShowLog = false;
					drawLog();
				}
				else {
					LogValue = 1;
					clearcircle(Log->x, Log->y, Log->radius);
					Log->draw(LogValue);
					isShowLog = true;
					drawLog();
				}

			}
			//落子
			else if (mGame.isin(msg.x, msg.y)) {
				count++;
				info.act = LUOZI;
				info.pos.x = msg.x;
				info.pos.y = msg.y;
				info.turn = turn;
				if (turn) {
					//当前为白棋下
					info.color = WHITEPIECE;
				}
				else {
					//当前为黑棋下
					info.color = BLACKPIECE;
				}
				if (!gm->doWork(info)) {
					flushmessage(EM_MOUSE);
					MessageBox(GetHWnd(), L"此位置不能下棋！", L"错误提示", 0);
					strLogs.push_back(info.strInfo);
					logOffset = 0;
					//strLog += info.strInfo;
					drawLog();
				}
				else {
					drawFunc();
					drawLog();
					turn = !turn;
					flushmessage(EM_MOUSE);
				}
				if (info.finish) {
					if (info.strInfo != L"") {
						strLogs.push_back(info.strInfo);
						logOffset = 0;
						drawLog();
					}
					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"白棋赢了！", L"", 0);
					}
					else if (info.winner == 1) {
						MessageBox(GetHWnd(), L"黑棋赢了", L"", 0);
					}
					else {
						MessageBox(GetHWnd(), L"平局", L"", 0);
					}
					break;
				}
			}
			//认输
			else if (renfu->isIn(msg.x, msg.y)) {
				info.act = RENFU;
				info.turn = turn;
				gm->doWork(info);
				if (info.finish) {
					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"白棋赢了！", L"", 0);
					}
					else if (info.winner == 1) {
						MessageBox(GetHWnd(), L"黑棋赢了!", L"", 0);
					}

					break;
				}
			}
			//悔棋
			else if (huiqi->isIn(msg.x, msg.y)) {
				info.act = HUIQI;
				info.turn = turn;
				gm->doWork(info);
				switch (info.state)
				{
				case 0:
				{
					MessageBox(GetHWnd(), L"此时不能悔棋！", L"提示", 0);
					break;
				}
				case 1:
				{
					MessageBox(GetHWnd(), L"悔棋次数已用完！", L"提示", 0);
					break;
				}
				default:
					break;
				}
				if (info.strInfo != L"") {
					strLogs.push_back(info.strInfo);
					logOffset = 0;
					drawLog();
				}
			}
			//保存
			else if (baocun->isIn(msg.x, msg.y)) {
				info.act = BAOCUN;
				info.turn = turn;
				if (gm->doWork(info)) {
					MessageBox(GetHWnd(), L"保存成功！", L"", 0);
				}
				else {
					MessageBox(GetHWnd(), L"保存失败！", L"", 0);
				}
			}
			//读入
			else if (duru->isIn(msg.x, msg.y)) {
				int num = gm->getMemNum();
				std::wstring wstr = L"当前有" + to_wstring(num) + L"个存档,请选择0~" + to_wstring(num - 1);
				wchar_t s[10];
				InputBox(s, 10, wstr.data());
				int state = _wtoi(s);
				//合法判断
				if (state >= num || state < 0) {
					MessageBox(GetHWnd(), L"输入错误，没有该存档！", L"", 0);
					strLogs.push_back(L"选择存档输入错误！\n");
					logOffset = 0;
					drawLog();
				}
				else {
					info.act = DURU;
					info.state = state;
					if (gm->doWork(info)) {
						MessageBox(GetHWnd(), L"读入成功！", L"", 0);
						turn = info.turn;
					}
					else {
						MessageBox(GetHWnd(), L"读入失败！", L"", 0);
					}
				}
			}
			//虚着
			else if (xuzhuo && xuzhuo->isIn(msg.x, msg.y)) {
				info.act = XUZHUO;
				info.turn = turn;
				gm->doWork(info);
				if (info.strInfo != L"") {
					strLogs.push_back(info.strInfo);
					logOffset = 0;
					drawLog();
				}
				if (info.finish) {

					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"白棋赢了！", L"", 0);
					}
					else {
						MessageBox(GetHWnd(), L"黑棋赢了", L"", 0);
					}
					break;
				}
				turn = !turn;
			}
			//重新开始
			else if (restart->isIn(msg.x, msg.y)) {
				info.act = CHONGKAI;
				info.turn = turn;
				if (gm->doWork(info)) {
					MessageBox(GetHWnd(), L"棋局重新开始！", L"", 0);
				}
				info.strInfo = L"";
				drawLog();

			}

			flushmessage(EM_MOUSE);
		}
		if (msg.wheel > 0) {
			if (logNum > strLogs.size()) {
				continue;
			}
			else {
				if (logOffset - 1 + index < 0) {
					continue;
				}
				else {
					logOffset--;
					drawLog();
					continue;
				}
			}
		}
		if (msg.wheel < 0) {
			if (logNum > strLogs.size()) {
				continue;
			}
			else {
				if (logOffset + index + logNum >= strLogs.size()) {
					continue;
				}
				else {
					logOffset++;
					drawLog();
					continue;
				}
			}
		}

		flushmessage(EM_MOUSE);
	}
}



void Client::initLayout() {
	initgraph(1200, 800);
	//游戏区域
	mGame.x = 0;
	mGame.y = 0;
	mGame.width = getheight();
	mGame.height = getheight();

	//功能区域
	mFunc.x = getheight();
	mFunc.y = 0;
	mFunc.width = getwidth() - getheight();
	mFunc.height = getheight() / 2;

	//日志区域
	mLog.x = getheight();
	mLog.y = getheight() / 2;
	mLog.width = getwidth() - getheight();
	mLog.height = getheight() / 2;

	auto pstyle = std::make_shared<LINESTYLE>();
	getlinestyle(pstyle.get());
	setlinestyle(PS_SOLID, 4);
	setlinecolor(BLACK);
	COLORREF tempColor = getfillcolor();
	setfillcolor(WHITE);         // 填充颜色设置

	fillrectangle(mGame.x, mGame.y, mGame.width, mGame.height);
	fillrectangle(mFunc.x, mFunc.y, mFunc.width + mFunc.x, mFunc.height + mFunc.y);
	fillrectangle(mLog.x, mLog.y, mLog.width + mLog.x, mGame.height + mLog.y);
}

//绘制游戏区域
void Client::drawGame() {
	gm->drawPieceBoard(mGame.x, mGame.y, mGame.width, mGame.height, gamePadding);
}

void Client::drawFunc() {
	int txtHeight = 30;
	settextstyle(txtHeight, 0, L"楷体");
	outtextxy(mFunc.x + mFunc.width / 2 - textwidth(L"功能区") / 2, mFunc.height / 10, L"功能区");
	//生成绘制功能按钮
	baocun = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"保存") / 2, mFunc.height / 4, L"保存");
	baocun->draw();
	duru = new TextButton(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"载入") / 2, mFunc.height / 4, L"载入");
	duru->draw();
	renfu = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"认输") / 2, mFunc.height / 4 + txtHeight * 2, L"认输");
	renfu->draw();
	huiqi = new TextButton(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"悔棋") / 2, mFunc.height / 4 + txtHeight * 2, L"悔棋");
	huiqi->draw();
	restart = new TextButton(mFunc.x + mFunc.width / 2 - textwidth(L"重新开始") / 2, mFunc.height / 4 + txtHeight * 8, L"重新开始");
	restart->draw();
	if (isweiqi) {
		xuzhuo = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"虚着") / 2, mFunc.height / 4 + txtHeight * 4, L"虚着");
		xuzhuo->draw();

		Log = new Radio(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"显示日志") / 2, mFunc.height / 4 + txtHeight * 5, 1);
		outtextxy(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"显示日志") / 2 + 10, mFunc.height / 4 + txtHeight * 4.5, L"显示日志");
		Log->draw(0);
	}
	else {
		Log = new Radio(mFunc.x + mFunc.width / 2 - textwidth(L"显示日志") / 2, mFunc.height / 4 + txtHeight * 5, 1);
		outtextxy(mFunc.x + mFunc.width / 2 - textwidth(L"显示日志") / 2 + 10, mFunc.height / 4 + txtHeight * 4.5, L"显示日志");
		Log->draw(0);
	}
}

void Client::drawLog() {
	clearrectangle(mLog.x, mLog.y, mLog.x + mLog.width, mLog.y + mLog.height);
	setfillcolor(WHITE);         // 填充颜色设置
	fillrectangle(mLog.x, mLog.y, mLog.width + mLog.x, mGame.height + mLog.y);
	int txtHeight = 30;
	settextcolor(BLUE);
	settextstyle(txtHeight, 0, L"楷体");
	outtextxy(mLog.x + mLog.width / 2 - textwidth(L"日志区") / 2, mLog.y + mLog.height / 10, L"日志区");

	if (isShowLog) {
		settextcolor(BLACK);
		settextstyle(15, 0, L"宋体");
		logNum = (mLog.height - mLog.height / 10 - 30 - 10) / 15;

		index = strLogs.size() - logNum;
		int lidx = index + logOffset;
		if (lidx < 0) {
			lidx = 0;
		}
		for (int i = lidx; i < strLogs.size() + logOffset; i++) {
			outtextxy(mLog.x, mLog.y + mLog.height / 10 + 30 + 15 * (i - lidx), strLogs[i].data());
		}

		if (logNum < strLogs.size()) {
			float ratio = logNum / float(strLogs.size());
			int lheight = mLog.height - mLog.height / 10 - 30;
			float itemheight = lheight / float(strLogs.size());
			float length = ratio * lheight;
			fillrectangle(mLog.x + mLog.width - 10, mLog.y + mLog.height / 10 + 30 + lidx * itemheight, mLog.x + mLog.width, mLog.y + mLog.height / 10 + 30 + lidx * itemheight + length);
		}
	}


}

void Client::drawPlayClient() {
	cleardevice();
	initLayout();
	setbkmode(TRANSPARENT);
	drawGame();
	drawFunc();
	drawLog();

}

void Client::setBackGroundColor(COLORREF color) {
	colorBackGround = color;
}

void Client::setImgBackGround(LPCTSTR path) {
	loadimage(&imgBackGround, path, width, height);
}

bool Client::isInputLegal(wchar_t* s, int& road) {
	road = _wtoi(s);
	if (road >= 8 && road <= 19) {
		return true;
	}
	else {
		return false;
	}
}