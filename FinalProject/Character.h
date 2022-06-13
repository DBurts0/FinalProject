#pragma once
class Character
{
protected:
	int health;
	int damage;
	int accuracy;
	int dodge;

public:
	int getHealth(int hp) {

		return hp;
	}

	int getDamage(int dmg) {

		return dmg;
	}

	int getAccuracy(int acc) {

		return acc;
	}

	int getDodge(int dod) {

		return dod;
	}
};

