#pragma once
#include <iostream>
#include "Character.h"
#include "PlayerItem.h"
#include "Enemy.h"
#include <windows.h>

using namespace std;
class Player : public Character
{
public:
	Character playerChar;

    int health = playerChar.getHealth(70); 
	int dodge = playerChar.getDodge(10);
    int accuracy;
    int damage;
    int critChance;

    string item[3] = { "Sword", "Dagger", "Bow" };
    string playerWeapon;

};

