#include "Client.h"
#include "GameFactory.h"
#include "GameManager.h"
#include <iostream>
#include <Windows.h>
#include <easyx.h>
#include <conio.h>
#include <vector>
#include <graphics.h>

using namespace std;


int main() {
	Client cl(800, 620);
	cl.init();
	cl.Start();
	if (!cl.getIsExit()) {
		return 0;
	}
	
	cl.play();
	closegraph();
	system("pause");
	return 0;
}

