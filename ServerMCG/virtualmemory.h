#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <QString>

using namespace std;

class VirtualMemory
{

private:
    static VirtualMemory *instance;

public:
    VirtualMemory();

    static VirtualMemory* getInstance();

    void generate_matrix();

    string getCard(string position);

    string types[40] = {"discord","facebook","github","google","instagram","linkedin","messenger","netflix","pinterest","skype",
                        "snapchat","spotify","telegram","tiktok","twitch","waze","whatsapp","wikipedia","youtube","zoom",
                        "discord","facebook","github","google","instagram","linkedin","messenger","netflix","pinterest","skype",
                        "snapchat","spotify","telegram","tiktok","twitch","waze","whatsapp","wikipedia","youtube","zoom"};

};

#endif // VIRTUALMEMORY_H
