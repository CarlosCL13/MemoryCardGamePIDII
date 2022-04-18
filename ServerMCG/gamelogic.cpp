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

string GameLogic::getType(string position){
    string answer;
    if(position1 == ""){
        position1 = position;
        answer = "FIR" + Memory::getInstance()->getinmemoryCard(position);
    }else{
        position2 = position;
        answer = "SEC" + Memory::getInstance()->getinmemoryCard(position);
    }

    return answer;
}

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
