#ifndef CARETAKER_H
#define CARETAKER_H

#include "Memento.h"
#include <string>
#include <fstream>


class Memento;

//备忘录管理类
class Caretaker
{
public:
	vector<Memento> m_vecMemento;
	int index = 0;
public:
	Caretaker();
	void Init();
	bool Save(Memento memento);
	bool Load(int state,Memento & mem);
};

#endif