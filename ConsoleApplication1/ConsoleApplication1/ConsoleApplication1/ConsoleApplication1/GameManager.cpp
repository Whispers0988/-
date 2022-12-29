#include "GameManager.h"


GameManager::GameManager() {

}

void GameManager::init(int road) {
	mPieceboard = new PieceBoard(road);
	caretaker = new Caretaker();
	caretaker->Init();
}

GameManager::~GameManager() {
	if (mPieceboard != nullptr) {
		delete mPieceboard;
	}
}

bool GameManager::doWork(ActionInfo& actInfo) {
	switch (actInfo.act)
	{
	case LUOZI:
	{
		return doLuozi(actInfo);
	}
	case RENFU:
	{
		actInfo.finish = true;
		actInfo.winner = actInfo.turn ? 1 : 0;
		break;
	}
	case HUIQI:
	{
		int result = doHuiqi(actInfo.turn);
		switch (result)
		{
		case 0:
		{
			actInfo.strInfo = L"下棋步数不足，不能悔棋！\n";
			break;
		}
		case 1:
		{
			actInfo.strInfo = L"悔棋次数不足!\n";
			break;
		}
		case 2:
		{
			mPieceboard->draw();
			break;
		}
		}
		actInfo.state = result;
		break;
	}
	case BAOCUN:
	{
		return doBaocun(actInfo.turn);
	}
	case DURU:
	{
		bool flag = doDuru(actInfo);
		if (flag) {
			mPieceboard->draw();
		}
		return flag;
	}
	case CHONGKAI:
	{
		return doChongkai(actInfo);
	}
	default:
		break;
	}
	return true;
}

bool GameManager::doAIWork(ActionInfo& actInfo) {
	return true;
}

void GameManager::createAI(int level, int type, int user) {
	AIfactory* aiFactory = nullptr;
	switch (level)
	{
	case 0:
		aiFactory = new E_AIfactory();
		break;
	case 1:
		aiFactory = new M_AIfactory();
		break;
	case 2:
		aiFactory = new D_AIfactory();
		break;
	default:
		break;
	}

	switch (type)
	{
	case 0:
		if (user == 1) {
			wuzi1 = aiFactory->creatWuziAI();
		}
		else if (user == 2) {
			wuzi2 = aiFactory->creatWuziAI();
		}
		
		break;
	case 2:
		if (user == 1) {
			heibai1 = aiFactory->creatHeibaiAI();
		}
		else if (user == 2) {
			heibai2 = aiFactory->creatHeibaiAI();
		}
		break;
	default:
		break;
	}
}

bool GameManager::doLuozi(ActionInfo& actInfo) {
	return true;
}

int GameManager::doHuiqi(bool turn) {
	//缓存队列不足以悔棋
	if (mPieceboard->lastPieces.size() < 2) {
		return 0;
	}

	//悔棋次数判断
	if (turn && times_W == 0) {
		return 1;
	}
	if (!turn && times_B == 0) {
		return 1;
	}

	for (int i = 0; i < 2; i++) {
		mPieceboard->undoPiece(mPieceboard->lastPieces.back());
		mPieceboard->lastPieces.pop_back();
	}
	if (turn) {
		times_W--;
	}
	else {
		times_B--;
	}
	return 2;
}

bool GameManager::doBaocun(bool turn) {
	auto mem = mPieceboard->Save(turn, times_B, times_W);
	return caretaker->Save(mem);
}

bool GameManager::doDuru(ActionInfo& info) {
	Memento mem;
	if (!caretaker->Load(info.state, mem)) {
		return false;
	}
	mPieceboard->lastPieces = mem.m_lastPieces;
	mPieceboard->setArr(mem.m_arr);
	times_B = mem.m_times_B;
	times_W = mem.m_times_W;
	info.turn = mem.m_turn;

	//重新计算棋盘参数
	mPieceboard->updatePieceBoard();

	return true;
}

bool GameManager::doChongkai(ActionInfo& info) {
	info.turn = false;
	times_W = 3;
	times_B = 3;
	mPieceboard->clearPieces();
	mPieceboard->clearDeque();

	mPieceboard->draw();
	return true;
}

int GameManager::getMemNum() {
	return caretaker->m_vecMemento.size();
}

void GameManager::drawPieceBoard(int startX, int startY, int width, int height, int padding) {
	mPieceboard->initBoard(startX, startY, width, height, padding);
	mPieceboard->draw();
}

bool GameManager::judge(int& winner) {
	return true;
}