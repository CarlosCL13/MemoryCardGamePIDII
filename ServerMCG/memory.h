#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <QImage>
#include "cards.h"
#include <map>
#include<time.h>


class Memory
{
private:
    static Memory *instance;



public:
    Memory();

    int pagehits = 0;

    int pagefaults = 0;

    static Memory* getInstance();

    Cards *ptrcards;

    map<string,Cards> memorymatrix;

    int imagesize();

    int freememory = 0;

    void start_matrix();

    string is_loaded_card(string position);

    string getinmemoryCard(string position);

    void loadcardinmemory(string position, string information);

    void erasecardinmemory(string position);

};

#endif // MEMORY_H
