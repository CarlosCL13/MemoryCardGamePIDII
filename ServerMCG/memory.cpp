#include "memory.h"
#include "cards.h"
#include "virtualmemory.h"
#include "mainwindow.h"

Memory *Memory::instance = nullptr;

Memory* Memory::getInstance() {
    if (instance == nullptr){
        instance = new Memory;
    }
    return instance;
}

Memory::Memory(){}


/**
 * @brief Memory::start_matrix initializes the in-memory array that is responsible for paging
 */

void Memory::start_matrix(){
    pagehits = 0;
    pagefaults = 0;
    int row;
    int column;
    srand(time(NULL));
    qDebug() << "Array in memory initialized";
    for(int i= 0;i< 15;i++){
        row = rand()%4;
        column = rand()%10;
        string position = to_string(row) + ":" + to_string(column);
        VirtualMemory::getInstance()->changeStatus(position);
        loadcardinmemory(position, VirtualMemory::getInstance()->getCard(position));
    }
}

/**
 * @brief Memory::loadcardinmemory load cards from disk to memory
 * @param position
 * @param information
 */

void Memory::loadcardinmemory(string position, string information){
    Cards *loaded_cards = new Cards();
    loaded_cards->position = position;
    loaded_cards->state = information[0];
    information.erase(0,1);
    loaded_cards->type = information;
    loaded_cards->size = imagesize();
    memorymatrix[position] = *loaded_cards;
    //cout << "The type is: " + memorymatrix[position].type << endl;
}

/**
 * @brief Memory::is_loaded_card check if a card is charged or not
 * @param position
 * @return
 */

string Memory::is_loaded_card(string position){
    string answer = "NO";

    if (memorymatrix.find(position) == memorymatrix.end()){
        return answer;
    }
    else{
        answer = memorymatrix[position].type;
    }

    return answer;
}

/**
 * @brief Memory::getinmemoryCard it is responsible for searching the memory for the requested card and loading it if it is not loaded
 * @param position
 * @return
 */

string Memory::getinmemoryCard(string position){
    string load = is_loaded_card(position);
    if(load != "NO"){
        pagehits++;
        cout << "Page Hits: " + to_string(pagehits) << endl;
        return load;
    }
    else{
        if(memorymatrix.size() < 15){
            loadcardinmemory(position, VirtualMemory::getInstance()->getCard(position));
        }
        else{
            memorymatrix.erase(prev(memorymatrix.end()));
            VirtualMemory::getInstance()->changeStatus(position);
            loadcardinmemory(position, VirtualMemory::getInstance()->getCard(position));
        }
        pagefaults++;
        cout << "Page Faults: " + to_string(pagefaults) << endl;
        return memorymatrix[position].type;
    }
}

/**
 * @brief Memory::erasecardinmemory
 * @param position
 */

void Memory::erasecardinmemory(string position){
    string positiontoerase = position;
    memorymatrix.erase(positiontoerase);
    int memorysize = memorymatrix.size();
    string size = to_string(memorysize);
    cout << "The memory size is: " + size << endl;
}


/**
 * @brief Memory::imagesize allows assigning the size of the image to each card object
 * @return
 */

int Memory::imagesize(){
    const char *imageName = ":/github.png";
    QImage img(imageName);
    int size = img.sizeInBytes();
    return size;
}
