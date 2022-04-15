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
    qDebug() << "Array in memory initialized";
    for(int i= 0;i< 15;i++){
        ptrcards[i] = nullptr;
    }
}

/**
 * @brief Memory::load_cards load cards from disk to memory
 * @param position
 * @param information
 * @return
 */

Cards* Memory::load_cards(string position, string information)
{
    Cards *loaded_cards = new Cards();
    loaded_cards->position = position;
    loaded_cards->state = information[0];
    information.erase(0,1);
    loaded_cards->type = information;
    loaded_cards->size = imagesize();
    return loaded_cards;

}

/**
 * @brief Memory::is_loaded check if a card is charged or not
 * @param position
 * @return
 */

string Memory::is_loaded(string position){
    string answer = "NO";

    for(int i= 0;i< 15;i++){

        if(ptrcards[i] != nullptr){
            if(ptrcards[i]->position == position){
                answer =  std::to_string(i);
                break;
            }

        }

    }

    //std::cout<<answer;
    return answer;

}

/**
 * @brief Memory::getCard it is responsible for searching the memory for the requested card and loading it if it is not loaded
 * @param position
 * @return
 */

string Memory::getCard(string position){
    std::string load = is_loaded(position);
       if(load != "NO"){

           return ptrcards[stoi(load)]->type;
       }
       else{
           if(freememory == 14){
               freememory = 0;
           }
           else{
               freememory += 1;
           }

           if(ptrcards[freememory] == nullptr){
               ptrcards[freememory]= load_cards(position,VirtualMemory::getInstance()->getCard(position));
           }

           else{
               VirtualMemory::getInstance()->changeStatus(ptrcards[freememory]->position);
               ptrcards[freememory]= load_cards(position, VirtualMemory::getInstance()->getCard(position));

           }


           return ptrcards[freememory]->type;
    }
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
