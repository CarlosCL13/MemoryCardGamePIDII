#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <QString>
#include <string>
#include <memory.h>
#include <mainwindow.h>
#include <gamelogic.h>
#include <memory.h>

class Handler
{
private:
    static Handler *instance;

public:
    Handler();

    static Handler* getInstance();

    QString player1;

    QString player2;

    QString turn;

    int player1_hits;

    int player2_hits;

    void getNames(QString name1, QString name2);

    void update_turn();

    void update_hits();

    void check_hits();

    void update_information();



};

#endif // HANDLER_H
