#include "GameFactory.h"

GameFactory::GameFactory() {}

GameManager* GameFactory::createGameManager(Type type, int road) {
	switch (type) {
	case WEIQI:
		return new WeiqiGameManager(road);
		break;
	case WUZIQI:
		return new WuziqiGameManager(road);
		break;
	case HEIBAI:
		return new HeibaiqiGameManager(road);
		break;
	default:
		break;
	}
}