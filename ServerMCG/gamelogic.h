#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <iostream>
#include <string>

using namespace std;

class GameLogic
{
private:
    static GameLogic *instance;


public:
    GameLogic();
    static GameLogic* getInstance();

    string position1;
    string position2;

    string getType(string position);
    string are_equals();

};

#endif // GAMELOGIC_H
