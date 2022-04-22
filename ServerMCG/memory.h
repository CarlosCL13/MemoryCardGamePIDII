#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <QImage>
#include "cards.h"
#include <string>
#include <map>
#include<time.h>


class Memory
{
private:
    static Memory *instance;



public:
    Memory();

    int pagehits;

    int pagefaults;

    static Memory* getInstance();

    Cards *ptrcards;

    map<string,Cards> memorymatrix;

    int imagesize(QString type);

    int memory_usage;

    void start_matrix();

    string is_loaded_card(string position);

    string getinmemoryCard(string position);

    void loadcardinmemory(string position, string information);

    void erasecardinmemory(string position);

    void shuffle();

    void dowload_cards();



};

#endif // MEMORY_H
