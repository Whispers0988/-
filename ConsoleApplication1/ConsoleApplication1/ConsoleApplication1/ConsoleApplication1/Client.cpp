#include "Client.h"
#include <locale>
#include <codecvt>

Client::Client(int w, int h) :width(w), height(h) {
	isExit = true;
}

void Client::LoginInit() {
	HWND hwnd = initgraph(width, height);
	loadimage(&imgBackGround, L"back.jpg", width, height);
	putimage(0, 0, &imgBackGround);
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, L"����");
	settextcolor(BLACK);
	outtextxy(180, 40, L"�����սƽ̨");

	//Log = new Radio(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"��ʾ��־") / 2, mFunc.height / 4 + txtHeight * 5, 1);
	settextstyle(40, 0, L"����");

	login_1 = new Radio(100, 170, 1);
	login_1->draw(0);
	outtextxy(120, 150, L"��¼");

	register_1 = new Radio(220, 170, 1);
	register_1->draw(0);
	outtextxy(240, 150, L"ע��");

	tourist_1 = new Radio(340, 170, 1);
	tourist_1->draw(0);
	outtextxy(360, 150, L"�ο�");

	ai_1 = new Radio(460, 170, 1);
	ai_1->draw(0);
	outtextxy(480, 150, L"AI");

	login_2 = new Radio(100, 370, 2);
	login_2->draw(0);
	outtextxy(120, 350, L"��¼");

	register_2 = new Radio(220, 370, 2);
	register_2->draw(0);
	outtextxy(240, 350, L"ע��");

	tourist_2 = new Radio(340, 370, 2);
	tourist_2->draw(0);
	outtextxy(360, 350, L"�ο�");

	ai_2 = new Radio(460, 370, 2);
	ai_2->draw(0);
	outtextxy(480, 350, L"AI");

	outtextxy(250, 250, L"���û�һ����ѡ��");

	submit1 = new TextButton(600, 250, L"ȷ��", YELLOW);
	submit1->draw();

	outtextxy(250, 450, L"���û�������ѡ��");

	submit2 = new TextButton(600, 450, L"ȷ��", YELLOW);
	submit2->draw();

	enterGame = new TextButton(280, 520, L"������Ϸ", YELLOW);
	enterGame->draw();

}

void Client::login() {
	//��ʼ���û�����ϵͳ
	um = new UserManager();
	um->loadFile();

	int user1_choice = -1;
	int user2_choice = -1;

	bool user1_finish = false;
	bool user2_finish = false;
	bool finishChoice = false;

	while (1) {
		ExMessage msg;
		getmessage(&msg, EM_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			//��ѡ���жϲ���
			if (login_1->isIn(msg.x, msg.y)) {
				user1_choice = 0;
				clearcircle(register_1->x, register_1->y, register_1->radius);
				clearcircle(tourist_1->x, tourist_1->y, tourist_1->radius);
				clearcircle(ai_1->x, ai_1->y, ai_1->radius);
				login_1->draw(1);
			}
			else if (register_1->isIn(msg.x, msg.y)) {
				user1_choice = 1;
				clearcircle(login_1->x, login_1->y, login_1->radius);
				clearcircle(tourist_1->x, tourist_1->y, tourist_1->radius);
				clearcircle(ai_1->x, ai_1->y, ai_1->radius);
				register_1->draw(1);
			}
			else if (tourist_1->isIn(msg.x, msg.y)) {
				user1_choice = 2;
				clearcircle(login_1->x, login_1->y, login_1->radius);
				clearcircle(register_1->x, register_1->y, register_1->radius);
				clearcircle(ai_1->x, ai_1->y, ai_1->radius);
				tourist_1->draw(1);
			}
			else if (ai_1->isIn(msg.x, msg.y)) {
				user1_choice = 3;
				clearcircle(login_1->x, login_1->y, login_1->radius);
				clearcircle(register_1->x, register_1->y, register_1->radius);
				clearcircle(tourist_1->x, tourist_1->y, tourist_1->radius);
				ai_1->draw(1);
			}
			else if (login_2->isIn(msg.x, msg.y)) {
				user2_choice = 0;
				clearcircle(register_2->x, register_2->y, register_2->radius);
				clearcircle(tourist_2->x, tourist_2->y, tourist_2->radius);
				clearcircle(ai_2->x, ai_2->y, ai_2->radius);
				login_2->draw(2);
			}
			else if (register_2->isIn(msg.x, msg.y)) {
				user2_choice = 1;
				clearcircle(login_2->x, login_2->y, login_2->radius);
				clearcircle(tourist_2->x, tourist_2->y, tourist_2->radius);
				clearcircle(ai_2->x, ai_2->y, ai_2->radius);
				register_2->draw(2);
			}
			else if (tourist_2->isIn(msg.x, msg.y)) {
				user2_choice = 2;
				clearcircle(login_2->x, login_2->y, login_2->radius);
				clearcircle(register_2->x, register_2->y, register_2->radius);
				clearcircle(ai_2->x, ai_2->y, ai_2->radius);
				tourist_2->draw(2);
			}
			else if (ai_2->isIn(msg.x, msg.y)) {
				user2_choice = 3;
				clearcircle(login_2->x, login_2->y, login_2->radius);
				clearcircle(register_2->x, register_2->y, register_2->radius);
				clearcircle(tourist_2->x, tourist_2->y, tourist_2->radius);
				ai_2->draw(2);
			}

			//�û���ť�ж��߼�
			if (submit1->isIn(msg.x, msg.y)) {
				switch (user1_choice)
				{
				case 0:
				{
					//�����¼
					wchar_t s_username[20];
					wchar_t s_password[20];
					InputBox(s_username, 20, L"�������û���");
					InputBox(s_password, 20, L"����������");

					std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
					std::string username = conv.to_bytes(s_username);
					std::string password = conv.to_bytes(s_password);

					UserManager::LOGINSTATE state = um->userLogin(username, password);
					switch (state)
					{
					case UserManager::SUCCESS:
						MessageBox(GetHWnd(), L"���һ��¼�ɹ�", L"��ʾ", 0);
						player1 = um->getUserByName(username);
						user1Choice = 0;
						break;
					case UserManager::USERNAMEFAIL:
						MessageBox(GetHWnd(), L"�û���������", L"����", 0);
						break;
					case UserManager::PASSWORDFAIL:
						MessageBox(GetHWnd(), L"�������", L"����", 0);
						break;
					default:
						break;
					}

					break;
				}
				case 1:
				{
					//����ע��
					wchar_t s_username[20];
					wchar_t s_password[20];
					InputBox(s_username, 20, L"���������û���");
					InputBox(s_password, 20, L"����������");

					std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
					std::string username = conv.to_bytes(s_username);
					std::string password = conv.to_bytes(s_password);

					if (um->addNewUser(username, password)) {
						MessageBox(GetHWnd(), L"���û�ע��ɹ�", L"��ʾ", 0);
						user1Choice = 1;
					}
					else {
						MessageBox(GetHWnd(), L"ע��ʧ��", L"����", 0);
					}
					break;
				}
				case 2:
				{
					//�����ο�
					MessageBox(GetHWnd(), L"���һѡ��ɹ������ο���ݵ�¼!", L"��ʾ", 0);
					user1Choice = 2;
					break;
				}
				case 3:
				{
					//����ai
					
					wchar_t sLevel[10];
					while (level1 != 1 && level1 != 2 && level1 != 3) {
						InputBox(sLevel, 10, L"��ѡ��ai�ȼ���1.�򵥣�2.�еȣ�3.����");
						level1 = _wtoi(sLevel);
						if (level1 != 1 && level1 != 2 && level1 != 3) {
							MessageBox(GetHWnd(), L"�����������������룡", L"����", 0);
						}
						else {
							break;
						}
					}
					user1Choice = 3;
					MessageBox(GetHWnd(), L"���һѡ��ɹ�������AI���в���!", L"��ʾ", 0);
					break;
				}
				default:
				{
					//û��ѡ��
					MessageBox(GetHWnd(), L"������ѡ��һ��������", L"����", 0);
					user1Choice = -1;
					break;
				}
				}
			}
			else if (submit2->isIn(msg.x, msg.y)) {
				switch (user2_choice)
				{
				case 0:
				{
					//�����¼
					wchar_t s_username[20];
					wchar_t s_password[20];
					InputBox(s_username, 20, L"�������û���");
					InputBox(s_password, 20, L"����������");

					std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
					std::string username = conv.to_bytes(s_username);
					std::string password = conv.to_bytes(s_password);

					UserManager::LOGINSTATE state = um->userLogin(username, password);
					switch (state)
					{
					case UserManager::SUCCESS:
						MessageBox(GetHWnd(), L"��Ҷ���¼�ɹ�", L"��ʾ", 0);
						player2 = um->getUserByName(username);
						user2Choice = 0;
						break;
					case UserManager::USERNAMEFAIL:
						MessageBox(GetHWnd(), L"�û���������", L"����", 0);
						break;
					case UserManager::PASSWORDFAIL:
						MessageBox(GetHWnd(), L"�������", L"����", 0);
						break;
					default:
						break;
					}
					break;
				}
				case 1:
				{
					//����ע��
					wchar_t s_username[20];
					wchar_t s_password[20];
					InputBox(s_username, 20, L"���������û���");
					InputBox(s_password, 20, L"����������");

					std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
					std::string username = conv.to_bytes(s_username);
					std::string password = conv.to_bytes(s_password);

					if (um->addNewUser(username, password)) {
						MessageBox(GetHWnd(), L"���û�ע��ɹ�", L"��ʾ", 0);
						user2Choice = 1;
					}
					else {
						MessageBox(GetHWnd(), L"ע��ʧ��", L"����", 0);
					}
					break;
				}
				case 2:
				{
					//�����ο�
					MessageBox(GetHWnd(), L"��Ҷ�ѡ��ɹ������ο���ݵ�¼!", L"��ʾ", 0);
					user2Choice = 2;
					break;
				}
				case 3:
				{
					//����ai
					
					wchar_t sLevel[10];
					while (level2 != 1 && level2 != 2 && level2 != 3) {
						InputBox(sLevel, 10, L"��ѡ��ai�ȼ���1.�򵥣�2.�еȣ�3.����");
						level2 = _wtoi(sLevel);
						if (level2 != 1 && level2 != 2 && level2 != 3) {
							MessageBox(GetHWnd(), L"�����������������룡", L"����", 0);
						}
						else {
							break;
						}
					}
					MessageBox(GetHWnd(), L"��Ҷ�ѡ��ɹ�������AI���в���!", L"��ʾ", 0);
					user2Choice = 3;
					break;
				}
				default:
				{
					//û��ѡ��
					MessageBox(GetHWnd(), L"������ѡ��һ��������", L"����", 0);
					user2Choice = -1;
					break;
				}
				}
			}
			else if (enterGame->isIn(msg.x, msg.y)) {
				if (user1Choice != -1 && user1Choice != 1 && user2Choice != -1 && user2Choice != 1) {
					MessageBox(GetHWnd(), L"����������Ϸѡ�����", L"��ʾ", 0);
					enterGameChoice = true;
				}
				else {
					MessageBox(GetHWnd(), L"����δ��ɣ�", L"��ʾ", 0);
				}
			}
		}

		if (enterGameChoice) {
			break;
		}
	}
}

void Client::init() {
	HWND hwnd = initgraph(width, height);
	setImgBackGround(L"back.jpg");

	setbkcolor(colorBackGround);
	cleardevice();
	loadimage(&imgBackGround, L"back.jpg", width, height);
	putimage(0, 0, &imgBackGround);
	SetWindowText(hwnd, L"�����սƽ̨");
	setbkmode(TRANSPARENT);
	settextstyle(80, 0, L"����");
	settextcolor(BLACK);
	outtextxy(180, 40, L"�����սƽ̨");
	wchar_t s[10];


	settextstyle(40, 0, L"����");
	weiqi.draw();
	wuziqi.draw();
	heibaiqi.draw();
	exit.draw();
}

//void Client::LOGIN() {
//	int w = 1000;
//	int h = 800;
//	HWND hwnd = initgraph(w, h);
//	setImgBackGround(L"back.jpg");
//	int txtHeight = 25;

//	setbkcolor(colorBackGround);
//	cleardevice();
//	loadimage(&imgBackGround, L"back.jpg", width, height);
//	putimage(0, 0, &imgBackGround);
//	SetWindowText(hwnd, L"��¼����");
//	setbkmode(TRANSPARENT);
//	settextstyle(80, 0, L"����");
//	settextcolor(BLACK);
//	outtextxy(180, 40, L"��ӭ������ɵ�¼");
//	wchar_t s[10];

//	settextstyle(txtHeight, 0, L"����");
//	outtextxy(w * 1 / 7 + 15, h * 1 / 3 - txtHeight / 2, L"�û�1��");
//	outtextxy(w * 1 / 7 + 15, h * 2 / 3 - txtHeight / 2, L"�û�2��");

//	login_1 = new Radio(w * 2 / 7 , h * 1 / 3 , 1);
//	outtextxy(w * 2 / 7 + 15, h * 1 / 3 - txtHeight / 2, L"��¼");
//	login_1->draw(0);

//	login_2 = new Radio(w * 2 / 7, h * 2 / 3, 1);
//	outtextxy(w * 2 / 7 + 15, h * 2 / 3 - txtHeight / 2, L"��¼");
//	login_2->draw(0);

//	register_1 = new Radio(w * 3 / 7, h * 1 / 3, 1);
//	outtextxy(w * 3 / 7 + 15, h * 1 / 3 - txtHeight / 2, L"ע��");
//	register_1->draw(0);

//	register_2 = new Radio(w * 3 / 7, h * 2 / 3, 1);
//	outtextxy(w * 3 / 7 + 15, h * 2 / 3 - txtHeight / 2, L"ע��");
//	register_2->draw(0);

//	tourist_1 = new Radio(w * 4 / 7, h * 1 / 3, 1);
//	outtextxy(w * 3 / 7 + 15, h * 1 / 3 - txtHeight / 2, L"�ο�");
//	tourist_1->draw(0);

//	tourist_2 = new Radio(w * 4 / 7, h * 2 / 3, 1);
//	outtextxy(w * 3 / 7 + 15, h * 2 / 3 - txtHeight / 2, L"�ο�");
//	tourist_2->draw(0);

//	ai_1 = new Radio(w * 5 / 7, h * 1 / 3, 1);
//	outtextxy(w * 5 / 7 + 15, h * 1 / 3 - txtHeight / 2, L"AI");
//	ai_1->draw(0);

//	ai_2 = new Radio(w * 5 / 7, h * 2 / 3, 1);
//	outtextxy(w * 5 / 7 + 15, h * 2 / 3 - txtHeight / 2, L"AI");
//	ai_2->draw(0);

	
//}

void Client::loadLog(std::wstring strInfo) {
	while (strInfo.find(L'\n') != wstring::npos) {
		int index = strInfo.find(L'\n');
		strLogs.push_back(strInfo.substr(0, index));
		strInfo.erase(0, index + 1);
	}
	strLogs.push_back(strInfo);
}

void Client::Start() {
	while (1) {
		ExMessage msg;
		getmessage(&msg, EM_MOUSE);
		wchar_t s[10];
		if (msg.lbutton) {
			if (weiqi.isIn(msg.x, msg.y)) {
				InputBox(s, 10, L"������Χ�����̴�С������ѡ��8~19");
				int road = -1;
				if (isInputLegal(s, road)) {
					Type type = WEIQI;
					gameType = type;
					GameFactory fc;
					gm = fc.createGameManager(type, road);
					isweiqi = true;
					break;
				}
				else {
					MessageBox(GetHWnd(), L"����������̴�С������Ϸ����ʧ�ܣ�", L"����", 0);
					flushmessage(EM_MOUSE);
					continue;
				}
			}
			else if (wuziqi.isIn(msg.x, msg.y)) {
				InputBox(s, 10, L"���������������̴�С������ѡ��8~19");
				int road = -1;
				if (isInputLegal(s, road)) {
					Type type = WUZIQI;
					gameType = type;
					GameFactory fc;
					gm = fc.createGameManager(type, road);
					//����������ai
					if (user1Choice == 3) {
						gm->createAI(level1 - 1, gameType,1);
					}
					if (user2Choice == 3) {
						gm->createAI(level2 - 1, gameType, 2);
					}

					isweiqi = false;
					break;
				}
				else {
					MessageBox(GetHWnd(), L"����������̴�С������Ϸ����ʧ�ܣ�", L"����", 0);
					flushmessage(EM_MOUSE);
					continue;
				}
			}
			else if (heibaiqi.isIn(msg.x, msg.y)) {
				InputBox(s, 10, L"������ڰ������̴�С������ѡ��8~19");
				int road = -1;
				if (isInputLegal(s, road)) {
					Type type = HEIBAI;
					gameType = type;
					GameFactory fc;
					gm = fc.createGameManager(type, road);
					//�����ڰ���ai
					if (user1Choice == 3) {
						gm->createAI(level1 - 1, gameType, 1);
					}
					if (user2Choice == 3) {
						gm->createAI(level2 - 1, gameType, 2);
					}
					isweiqi = false;
					break;
				}
				else {
					MessageBox(GetHWnd(), L"����������̴�С������Ϸ����ʧ�ܣ�", L"����", 0);
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
	bool turn = false;//��������
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
			//����
			else if (mGame.isin(msg.x, msg.y)) {
				count++;
				info.act = LUOZI;
				info.pos.x = msg.x;
				info.pos.y = msg.y;
				info.turn = turn;
				if (turn) {
					//��ǰΪ������
					info.color = WHITEPIECE;
				}
				else {
					//��ǰΪ������
					info.color = BLACKPIECE;
				}
				if (!gm->doWork(info)) {
					flushmessage(EM_MOUSE);
					MessageBox(GetHWnd(), L"��λ�ò������壡", L"������ʾ", 0);
					loadLog(info.strInfo);
					//strLogs.push_back(info.strInfo);
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
						loadLog(info.strInfo);
						//strLogs.push_back(info.strInfo);
						logOffset = 0;
						drawLog();
					}
					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"����Ӯ�ˣ�", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][0]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][1]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					else if (info.winner == 1) {
						MessageBox(GetHWnd(), L"����Ӯ��", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][1]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][0]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					else {
						MessageBox(GetHWnd(), L"ƽ��", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][2]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][2]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					break;
				}
			}
			//����
			else if (renfu->isIn(msg.x, msg.y)) {
				info.act = RENFU;
				info.turn = turn;
				gm->doWork(info);
				if (info.finish) {
					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"����Ӯ�ˣ�", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][0]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][1]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					else if (info.winner == 1) {
						MessageBox(GetHWnd(), L"����Ӯ��!", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][1]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][0]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}

					break;
				}
			}
			//����
			else if (huiqi->isIn(msg.x, msg.y)) {
				info.act = HUIQI;
				info.turn = turn;
				gm->doWork(info);
				switch (info.state)
				{
				case 0:
				{
					MessageBox(GetHWnd(), L"��ʱ���ܻ��壡", L"��ʾ", 0);
					break;
				}
				case 1:
				{
					MessageBox(GetHWnd(), L"������������꣡", L"��ʾ", 0);
					break;
				}
				default:
					break;
				}
				if (info.strInfo != L"") {
					loadLog(info.strInfo);
					//strLogs.push_back(info.strInfo);
					logOffset = 0;
					drawLog();
				}
			}
			//����
			else if (baocun->isIn(msg.x, msg.y)) {
				info.act = BAOCUN;
				info.turn = turn;
				if (gm->doWork(info)) {
					MessageBox(GetHWnd(), L"����ɹ���", L"", 0);
				}
				else {
					MessageBox(GetHWnd(), L"����ʧ�ܣ�", L"", 0);
				}
			}
			//����
			else if (duru->isIn(msg.x, msg.y)) {
				int num = gm->getMemNum();
				std::wstring wstr = L"��ǰ��" + to_wstring(num) + L"���浵,��ѡ��0~" + to_wstring(num - 1);
				wchar_t s[10];
				InputBox(s, 10, wstr.data());
				int state = _wtoi(s);
				//�Ϸ��ж�
				if (state >= num || state < 0) {
					MessageBox(GetHWnd(), L"�������û�иô浵��", L"", 0);
					//strLogs.push_back(L"ѡ��浵�������\n");
					loadLog(info.strInfo);
					logOffset = 0;
					drawLog();
				}
				else {
					info.act = DURU;
					info.state = state;
					if (gm->doWork(info)) {
						MessageBox(GetHWnd(), L"����ɹ���", L"", 0);
						turn = info.turn;
					}
					else {
						MessageBox(GetHWnd(), L"����ʧ�ܣ�", L"", 0);
					}
				}
			}
			//����
			else if (xuzhuo && xuzhuo->isIn(msg.x, msg.y)) {
				info.act = XUZHUO;
				info.turn = turn;
				gm->doWork(info);
				if (info.strInfo != L"") {
					//strLogs.push_back(info.strInfo);
					loadLog(info.strInfo); 
					logOffset = 0;
					drawLog();
				}
				if (info.finish) {

					if (info.winner == 0) {
						MessageBox(GetHWnd(), L"����Ӯ�ˣ�", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][0]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][1]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					else {
						MessageBox(GetHWnd(), L"����Ӯ��", L"", 0);
						if (user2Choice == 0) {
							auto tempArray = player2->getInfo();
							tempArray[gameType][1]++;
							player2->setArray(tempArray);
						}
						if (user1Choice == 0) {
							auto tempArray = player1->getInfo();
							tempArray[gameType][0]++;
							player1->setArray(tempArray);
						}
						um->saveFile();
					}
					break;
				}
				turn = !turn;
			}
			//���¿�ʼ
			else if (restart->isIn(msg.x, msg.y)) {
				info.act = CHONGKAI;
				info.turn = turn;
				if (gm->doWork(info)) {
					MessageBox(GetHWnd(), L"������¿�ʼ��", L"", 0);
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

		//����ai
		if (turn && user2Choice == 3) {
			//����ai
			ActionInfo info;
			info.color = WHITEPIECE;
			gm->doAIWork(info);
			drawFunc();
			drawLog();
			turn = !turn;
			if (info.finish) {
				if (info.strInfo != L"") {
					loadLog(info.strInfo);
					//strLogs.push_back(info.strInfo);
					logOffset = 0;
					drawLog();
				}
				if (info.winner == 0) {
					MessageBox(GetHWnd(), L"����Ӯ�ˣ�", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][0]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][1]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				else if (info.winner == 1) {
					MessageBox(GetHWnd(), L"����Ӯ��", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][1]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][0]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				else {
					MessageBox(GetHWnd(), L"ƽ��", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][2]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][2]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				break;
			}
		}
		if (!turn && user1Choice == 3) {
			//����ai
			ActionInfo info;
			info.color = BLACKPIECE;
			gm->doAIWork(info);
			drawFunc();
			drawLog();
			turn = !turn;
			if (info.finish) {
				if (info.strInfo != L"") {
					loadLog(info.strInfo);
					//strLogs.push_back(info.strInfo);
					logOffset = 0;
					drawLog();
				}
				if (info.winner == 0) {
					MessageBox(GetHWnd(), L"����Ӯ�ˣ�", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][0]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][1]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				else if (info.winner == 1) {
					MessageBox(GetHWnd(), L"����Ӯ��", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][1]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][0]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				else {
					MessageBox(GetHWnd(), L"ƽ��", L"", 0);
					if (user2Choice == 0) {
						auto tempArray = player2->getInfo();
						tempArray[gameType][2]++;
						player2->setArray(tempArray);
					}
					if (user1Choice == 0) {
						auto tempArray = player1->getInfo();
						tempArray[gameType][2]++;
						player1->setArray(tempArray);
					}
					um->saveFile();
				}
				break;
			}
		}


		flushmessage(EM_MOUSE);
	}
}



void Client::initLayout() {
	initgraph(1200, 800);
	//��Ϸ����
	mGame.x = 0;
	mGame.y = 0;
	mGame.width = getheight();
	mGame.height = getheight();

	//��������
	mFunc.x = getheight();
	mFunc.y = 0;
	mFunc.width = getwidth() - getheight();
	mFunc.height = getheight() / 2;

	//��־����
	mLog.x = getheight();
	mLog.y = getheight() / 2;
	mLog.width = getwidth() - getheight();
	mLog.height = getheight() / 2;

	auto pstyle = std::make_shared<LINESTYLE>();
	getlinestyle(pstyle.get());
	setlinestyle(PS_SOLID, 4);
	setlinecolor(BLACK);
	COLORREF tempColor = getfillcolor();
	setfillcolor(WHITE);         // �����ɫ����

	fillrectangle(mGame.x, mGame.y, mGame.width, mGame.height);
	fillrectangle(mFunc.x, mFunc.y, mFunc.width + mFunc.x, mFunc.height + mFunc.y);
	fillrectangle(mLog.x, mLog.y, mLog.width + mLog.x, mGame.height + mLog.y);
}

//������Ϸ����
void Client::drawGame() {
	gm->drawPieceBoard(mGame.x, mGame.y, mGame.width, mGame.height, gamePadding);
}

void Client::drawFunc() {
	int txtHeight = 30;
	settextstyle(txtHeight, 0, L"����");
	outtextxy(mFunc.x + mFunc.width / 2 - textwidth(L"������") / 2, mFunc.height / 10, L"������");
	//���ɻ��ƹ��ܰ�ť
	baocun = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"����") / 2, mFunc.height / 4, L"����");
	baocun->draw();
	duru = new TextButton(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"����") / 2, mFunc.height / 4, L"����");
	duru->draw();
	renfu = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"����") / 2, mFunc.height / 4 + txtHeight * 2, L"����");
	renfu->draw();
	huiqi = new TextButton(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"����") / 2, mFunc.height / 4 + txtHeight * 2, L"����");
	huiqi->draw();
	restart = new TextButton(mFunc.x + mFunc.width / 2 - textwidth(L"���¿�ʼ") / 2, mFunc.height / 4 + txtHeight * 8, L"���¿�ʼ");
	restart->draw();
	luxiang = new TextButton(mFunc.x + textwidth(L"¼��") / 2 + 5, mFunc.height / 4 + txtHeight * 8, L"¼��");
	luxiang->draw();
	huifang = new TextButton(mFunc.x + mFunc.width - textwidth(L"�ط�") * 3 / 2 - 5, mFunc.height / 4 + txtHeight * 8, L"�ط�");
	huifang->draw();
	if (isweiqi) {
		xuzhuo = new TextButton(mFunc.x + mFunc.width / 4 - textwidth(L"����") / 2, mFunc.height / 4 + txtHeight * 4, L"����");
		xuzhuo->draw();

		Log = new Radio(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"��ʾ��־") / 2, mFunc.height / 4 + txtHeight * 5, 1);
		outtextxy(mFunc.x + mFunc.width * 3 / 4 - textwidth(L"��ʾ��־") / 2 + 10, mFunc.height / 4 + txtHeight * 4.5, L"��ʾ��־");
		Log->draw(0);
	}
	else {
		Log = new Radio(mFunc.x + mFunc.width / 2 - textwidth(L"��ʾ��־") / 2, mFunc.height / 4 + txtHeight * 5, 1);
		outtextxy(mFunc.x + mFunc.width / 2 - textwidth(L"��ʾ��־") / 2 + 10, mFunc.height / 4 + txtHeight * 4.5, L"��ʾ��־");
		Log->draw(0);
	}

	//���һ��ս��Ϣ
	if (user1Choice == 0) {
		//������ʾ��Ϣ
		std::wstring info;
		std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
		auto infoArray = player1->getInfo();
		std::wstring username = conv.from_bytes(player1->getUserName());
		info = info + L"���壺" + username + L",��ʷս����" + L"ʤ��" + std::to_wstring(infoArray[gameType][0])
			+ L",����" + std::to_wstring(infoArray[gameType][1])
			+ L",ƽ��" + std::to_wstring(infoArray[gameType][2]);
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 40, info.c_str());
	}
	else if (user1Choice == 2) {
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 40, L"���壺�ο�");
	}
	else if (user1Choice == 3) {
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 40, L"���壺AI");
	}
	//��Ҷ���ս��Ϣ
	if (user2Choice == 0) {
		//������ʾ��Ϣ
		std::wstring info;
		std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
		auto infoArray = player2->getInfo();
		std::wstring username = conv.from_bytes(player2->getUserName());
		info = info + L"���壺" + username + L",��ʷս����" + L"ʤ��" + std::to_wstring(infoArray[gameType][0])
			+ L",����" + std::to_wstring(infoArray[gameType][1])
			+ L",ƽ��" + std::to_wstring(infoArray[gameType][2]);
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 70, info.c_str());
	}
	else if (user2Choice == 2) {
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 70, L"���壺�ο�");
	}
	else if (user2Choice == 3) {
		settextstyle(15, 0, L"����");
		outtextxy(mFunc.x + 20, mFunc.height / 4 + txtHeight * 4.5 + 70, L"���壺AI");
	}
}

void Client::drawLog() {
	clearrectangle(mLog.x, mLog.y, mLog.x + mLog.width, mLog.y + mLog.height);
	setfillcolor(WHITE);         // �����ɫ����
	fillrectangle(mLog.x, mLog.y, mLog.width + mLog.x, mGame.height + mLog.y);
	int txtHeight = 30;
	settextcolor(BLUE);
	settextstyle(txtHeight, 0, L"����");
	outtextxy(mLog.x + mLog.width / 2 - textwidth(L"��־��") / 2, mLog.y + mLog.height / 10, L"��־��");

	if (isShowLog) {
		settextcolor(BLACK);
		settextstyle(15, 0, L"����");
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