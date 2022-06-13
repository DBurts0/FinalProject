#pragma once
#include <iostream>
#include "Character.h"
#include "Player.h"

using namespace std;
class Enemy : public Character
{
public:
	Character enemyChar;
	int health = 40;
	int damage;
	int dodge;
	int accuracy;
    int critChance;

    void Attack()
    {
        accuracy = 1 + (rand() % 100);
        if (accuracy >= 50) 
        {
            critChance = 1 + (rand() % 65);
            damage = 5 + (rand() % 10);
            cout << "Enemy crit chance is: " << critChance << endl;
            if (critChance >= 45)
            {
                cout << "Critical hit!\n";
                cout << "The enemy is dealing " << damage * 2 << " damage.\n";
            }
            else
            {
                cout << "The enemy is dealing " << damage << " damage.\n";
            }
        }
        else
        {
            cout << "You dodged the attack!\n\n";
        }
        
    }


};


