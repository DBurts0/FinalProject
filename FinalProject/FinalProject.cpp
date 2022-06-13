// FinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "PlayerItem.h"
using namespace std;

int roundCount = 0;
int enemiesDefeated = 0;

string playerAction;
string enemyAction[2] = {"Attack", "Defend"};
Player player;
Enemy enemy;
PlayerItem pItem;

void Quit() 
{
    // Quit the program
    exit(0);
}
void Leaderboard() 
{
    fstream leaderboard("leaderboard.txt");
    leaderboard.open("leaderboard.txt");
    string score;

    playerAction.clear();
    cout << "Do you want to see the leaderboard?\n";
    while (playerAction != "yes" && playerAction != "no")
    {
        cin >> playerAction;
        if (playerAction == "yes")
        {
            // Read out the leaderboard
            while (getline(leaderboard, score))
            {
                cout << score << endl;
            }
            // close the file
            leaderboard.close();
        }
        else if (playerAction == "no")
        {
            leaderboard.close();
            Quit();
        }
    }
    playerAction.clear();
    cout << "Do you want to add your score?\n\n";
    while (playerAction != "yes" && playerAction != "no")
    {
        cin >> playerAction;
        if (playerAction == "yes")
        {
            leaderboard.open("leaderboard.txt", ios::out | ios::in | ios::app);
            string playerName;
            cout << "Enter a name.\n";
            cin >> playerName;
            playerName.append(" ");
            // add the player's name and how many enemies they defeated
            leaderboard << playerName;
            leaderboard << enemiesDefeated;
            leaderboard << "\n";
            leaderboard.close();           
        }
        else if (playerAction == "no")
        {
            leaderboard.close();
            Quit();
        }
    }
    
    
}



void StatBoost(int dmg, int acc, int crit)
{
    // increase the player's stats based on the weapon equipped
    if (pItem.itemSelect == 0)
    {
        player.damage += dmg;
    }
    if (pItem.itemSelect == 1)
    {
        player.critChance += crit;
    }
    if (pItem.itemSelect == 2)
    {
        player.accuracy += acc;
    }
}

void Attack()
{
    player.critChance = 1 + (rand() % 65);
    player.damage = 5 + (rand() % 10);
    // apply a damage boost if the player has a sword
    if (player.playerWeapon == player.item[0])
    {
        StatBoost(5, 0, 0);
        cout << "Sword bonus: +5 damage\n";
    }
    // apply a crit chance boost if the player has a dagger
    else if (player.playerWeapon == player.item[1])
    {
        StatBoost(0, 0, 5);
        cout << "Dagger bonus: +5 crit\n";
    }

    cout << "Crit chance is: " << player.critChance << endl;
    if (player.critChance >= 45)
    {
        cout << "Critical hit!\n";
        cout << "Dealing " << player.damage * 2 << " damage.\n";
    }
    else
    {
        cout << "Dealing " << player.damage << " damage.\n";
    }
}

void hitChance()
{
    player.accuracy = 1 + (rand() % 100);
    // apply an accuracy boost if the player has a bow
    if (player.playerWeapon == player.item[2])
    {
        StatBoost(0, 10, 0);
        cout << "Bow bonus: +10 accuracy\n";
    }
    cout << "Hit chance: " << player.accuracy << endl;
    if (player.accuracy >= 50)
    {
        Attack();
    }
    else
    {
        cout << "You missed!\n\n";
        player.damage = 0;
    }
}


void combat() 
{
        // display the amount of rounds
        roundCount++;
        cout << "Round " << roundCount << endl;

        // check if the player will hit the enemy
        hitChance();        
        enemy.health -= player.damage;
        Sleep(1000);
        if (enemy.health >= 0)
        {
            // check if the enemy will hit the player
            enemy.Attack();
            player.health -= enemy.damage;

        }
        Sleep(1000);
        // display how much health the player and enemy have
        cout << "Player health: " << player.health << endl;
        cout << "Enemy health: " << enemy.health << endl << endl;
        Sleep(1000);
    if (enemy.health <= 0)
    {
        enemiesDefeated++;
        // check if the player wants to equip the new weapon
        int drop = rand() % 3;
        cout << "The enemy has dropped a " << player.item[drop] << endl;
        cout << "Do you wish to equip it?\n";
        string equipDrop;
        while (equipDrop != "yes" && equipDrop != "no")
        {
            cin >> equipDrop;
        }
        if (equipDrop == "yes")
        {
            player.playerWeapon = player.item[drop];
            cout << "\nYou equiped the " << player.item[drop] << endl << endl;
        }
        else
        {
            cout << "\n You leave the weapon alone\n\n";
        }

        // ask the player if the want to continue fighting
        cout << "Do you wish to continue?\n";
        playerAction.clear();
        while (playerAction != "yes" && playerAction != "no")
        {
            cin >> playerAction;
            if (playerAction == "yes")
            {
                roundCount = 0;
                cout << "A new enemy approaches while you heal your wounds.\n";
                player.health = 70;
                enemy.health = 40;
            }
            else if (playerAction == "no")
            {
                cout << "You have done all you could and defeated: " << enemiesDefeated << " enemies.\n";
                Leaderboard();
            }
        }
    }
    else if (player.health <= 0)
    {
        cout << "You have been defeated!\n";
        cout << "You have done all you could and defeated: " << enemiesDefeated << " enemies.\n\n";
        Leaderboard();
    }
}

void Play() 
{
    playerAction.clear();
    cout << "Choose a weapon to start with.\n";
    cout << "Options: sword, dagger, bow\n";
    while (playerAction != "sword" && playerAction != "dagger" && playerAction != "bow")
    {
        cin >> playerAction;
        if (playerAction == "sword")
        {
            player.playerWeapon == player.item[0];
            cout << "Sword equiped, increasing attack damage.\n\n";
        }
        else if (playerAction == "dagger")
        {
            player.playerWeapon == player.item[1];
            cout << "Dagger equiped, increasing crit chance.\n\n";
        }
        else if (playerAction == "bow")
        {
            player.playerWeapon == player.item[2];
            cout << "Bow equiped, increasing accuracy.\n\n";
        }
    }

    while (player.health > 0 && enemy.health >= 0)
    {
        combat();
    }

}

void Tutorial() 
{
    cout << "Do you wish to do the tutorial?\n";
    cout << "Type 'yes' or 'no'\n\n";
    playerAction.clear();
    
    while (playerAction != "yes" && playerAction != "no")
    {
        cin >> playerAction;
        if (playerAction == "no")
        {
            cout << "Skipping the tutorial.\n\n";
            Sleep(2000);

        }
        else if (playerAction == "yes")
        {
            // explain how the game works
            cout << "Each round the player and the enemy will take rounds attacking.\n";
            Sleep(3000);
            cout << "The player will gain different stat bonuses based on which type of weapon they have.\n";
            Sleep(3000);
            cout << "Swords will give bonus damage, daggers will increase your chance of a critical hit, and bows increase your accuracy.\n";
            Sleep(3000);
            cout << "If the player successfully defeats the enemy they will gain the option to change to a new weapon before continuing.\n";
            Sleep(3000);
            cout << "The player can also quit after each battle and have the option to post their score on the leaderboard.\n\n";
            Sleep(3000);
        }
            // give th eplayer the option to play or quit
            cout << "Are you ready to play?\n";
            cout << "Type 'yes' or 'no'\n";
            playerAction.clear();
            cin >> playerAction;
        
            if (playerAction == "yes") 
            {
                Play();
            }
            else if (playerAction == "no")
            {
                Quit();
            }
        
    }
}

void Menu()
{
    cout << "Welcome warrior, there is a caravan heading east in need of an extra guard.\n";
    Sleep(4000);
    cout << "Are you willing to take the job?\n";
    Sleep(2000);

    cout << "Type 'yes' or 'no'\n";
    
    while (playerAction != "yes" && playerAction != "no")
    {
        cin >> playerAction;
        if (playerAction == "no")
        {
            cout << "Understood, I'll be here if you're very looking for work.\n";
            Leaderboard();
        }
        else if (playerAction == "yes")
        {
            cout << "I'll inform the client that you will join them. We'll leave tomorrow\n\n";
            Tutorial();
        }
    }
    
}

int main()
{
    srand(time(0));
    Menu();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
