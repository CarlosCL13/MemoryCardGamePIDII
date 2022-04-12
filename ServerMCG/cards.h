#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <iostream>

using namespace std;

class Cards
{
public:
    Cards();

    int pos_i, pos_j, id, memory;

    Cards(int pos_i, int pos_j, int id, int memory);

    void obtener_imagen(int id);

    void print() const;
};

#endif // CARDS_H
