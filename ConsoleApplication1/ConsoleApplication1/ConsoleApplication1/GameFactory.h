#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "GameManager.h"
#include "WeiQiManager.h"
#include "WuziqiManager.h"

class GameFactory
{
public:
	GameFactory();

	GameManager* createGameManager(Type type, int road);

};

#endif