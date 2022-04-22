#include "handler.h"

Handler *Handler::instance = nullptr;

Handler* Handler::getInstance() {
    if (instance == nullptr){
        instance = new Handler;
    }
    return instance;
}

Handler::Handler(){}
/**
 * @brief Handler::update_information It is in charge of updating data such as shifts, eliminating the discovered pairs
 * that are in memory and updating the hits.
 */

void Handler::update_information(){
    Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position1);
    Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position2);
    GameLogic::getInstance()->position1 = "";
    GameLogic::getInstance()->position2 = "";
    update_turn();
    check_hits();
}

/**
 * @brief Handler::getNames
 * @param name1
 * @param name2
 */

void Handler::getNames(QString name1, QString name2){
    player1 = name1;
    player2 = name2;

}

/**
 * @brief Handler::update_turn
 */

void Handler::update_turn(){
    if(turn == player1){
        turn = player2;
    }else{
        turn = player1;
    }
}

/**
 * @brief Handler::update_hits controls the number of successes of pairs of cards of each player
 */

void Handler::update_hits(){
    if(turn == player1){
        player1_hits++;
    }else{
        player2_hits++;
    }

}

/**
 * @brief Handler::check_hits check the number of hits of each player, if any is equal to three activate a point booster
 */

void Handler::check_hits(){
    if(player1_hits == 3){
        player1_hits=0;
        MainWindow::getInstance()->onSendButtonPressed(player1+",""HITSPW");
    }else if(player2_hits == 3){
        player2_hits=0;
        MainWindow::getInstance()->onSendButtonPressed(player2+",""HITSPW");
    }else{
        cout << "Not enough hits" << endl;
    }
}


