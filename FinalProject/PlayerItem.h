#pragma once
#include "Player.h"
#include <iostream>
#include <windows.h>
using namespace std;

class PlayerItem 
{
public:
	
	int itemSelect;

	int ChooseItem()
	{
		srand(time(0));
		
		string item[3] = { "Sword", "Dagger", "Bow" };
		itemSelect = rand() % 3;
		return itemSelect;
	}
};

