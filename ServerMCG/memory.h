#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <QImage>
#include <QHash>
#include "cards.h"

class Memory
{
private:
    static Memory *instance;



public:
    Memory();

    static Memory* getInstance();

    Cards *ptrcards[15];

    int imagesize();

    int freememory = 0;

    void start_matrix();

    string is_loaded(string position);

    string getCard(string position);

    Cards * load_cards(std::string position, std::string information);

};

#endif // MEMORY_H
