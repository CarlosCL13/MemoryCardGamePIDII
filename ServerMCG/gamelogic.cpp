#include "gamelogic.h"
#include "memory.h"


GameLogic *GameLogic::instance = nullptr;

GameLogic* GameLogic::getInstance() {
    if (instance == nullptr){
        instance = new GameLogic;
    }
    return instance;
}

GameLogic::GameLogic(){}

/**
 * @brief GameLogic::getType searches in memory for the type of card according to the position of the matrix received
 * @param position
 * @return
 */

string GameLogic::getType(string position){
    string answer;
    if(position1 == ""){
        position1 = position;
        answer = Memory::getInstance()->getinmemoryCard(position);
    }else{
        position2 = position;
        answer = Memory::getInstance()->getinmemoryCard(position);
    }

    return answer;
}

/**
 * @brief GameLogic::are_equals
 * @return
 */

string GameLogic::are_equals(){
    string type1 = Memory::getInstance()->getinmemoryCard(position1);
    string type2 = Memory::getInstance()->getinmemoryCard(position2);
    if(type1 == type2){
        return "YES";
    }
    else{
        return "NO";
    }

}
