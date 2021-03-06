#include "virtualmemory.h"
#include "mainwindow.h"

VirtualMemory *VirtualMemory::instance = nullptr;

VirtualMemory* VirtualMemory::getInstance() {
    if (instance == nullptr){
        instance = new VirtualMemory;
    }
    return instance;
}

VirtualMemory::VirtualMemory(){}

/**
 * @brief VirtualMemory::generate_matrix
 */
void VirtualMemory::generate_matrix(){
    ofstream archive;
    archive.open("Disk.txt", ios::out);
    archive<<"";
    archive.close();
    archive.open("Disk.txt",ios::app);
    if(archive.fail()){
        cout << "Can't open the disk" << endl;
        exit(1);
    }
     for(int i = 0;i < 4;i++){
        for(int j = 0; j < 10; j++){
                string information;
                information += "f";
                srand (time(NULL));

                while(true){

                    int position = rand() % 40;

                    if(types[position] != ""){

                        information += types[position];
                        types[position] = "";
                        break;
                    }
                }

                information += "]";
                archive<<information;
        }
        archive<<"\n";

    }
    archive.close();

}

/**
 * @brief VirtualMemory::getCard allows you to search from a given position what card is in that position on the disk
 * @param position
 * @return
 */
string VirtualMemory::getCard(std::string position){

    std::ifstream archive;
    archive.open("Disk.txt",std::ios::in);
    if(archive.fail()){
        std::cout<<"Can't open the disk";
    }
    std::string information;
    std::string typeCard;
    int row = 0;
    while (getline(archive, information)) {
        int column = 0;
        int length = information.length();
        for(int i= 0 ;i <= length;i++){
            std::string parenthesis;
            parenthesis += information[i];
            std::string position2 = std::to_string(row) + ":" +std::to_string(column);
            if(position == position2){
                //std::string typeCard;
                int j = i;
                while(true){
                    std::string parenthesis2;
                    parenthesis2 += information[j];
                    if (parenthesis2 == "]"){
                        //std::cout << typeCard << std::endl;
                        return typeCard;
                    }
                    else{
                        typeCard += parenthesis2 ;
                        j += 1;
                    }
                }
            }
            if (parenthesis == "]"){
                column += 1;
            }
        }
        row += 1;
    }
    archive.close();
    return typeCard;

}

/**
 * @brief VirtualMemory::changeStatus allows to change the state of the cards on the disk
 * @param position
 */
void VirtualMemory::changeStatus(string position){
    std::ifstream archive;
    archive.open("Disk.txt",std::ios::in);
    if(archive.fail()){
        std::cout<<"Can't open the disk";
    }
    std::string text;

    std::string information;

    while (getline(archive, text)) {
        information += text;
        information += "\n";
    }
    archive.close();
    int length = information.length();
    int raw = 0;
    int column = 0;
    std::string changed_text;
    for(int i= 0 ;i <= length;i++){

        std::string parenthesis;
        parenthesis +=information[i];
        std::string position2 = std::to_string(raw) + ":" +std::to_string(column);
        if(position == position2 ){
            changed_text += "t";
            position = "find it";
        }
        else{
            changed_text += parenthesis;
        }
        if(column == 10){
            raw += 1;
            column = 0;
            continue;
            std::cout<<raw<<std::endl;
        }
        if(parenthesis == "]"){
            column += 1;
        }
    }
    std::ofstream archive2;
    archive2.open("Disk.txt",std::ios::out);
    archive2<<changed_text;
    archive2.close();
}

/**
 * @brief VirtualMemory::dowload_statuscard changes the status of a card being removed from memory
 * @param position
 */

void VirtualMemory::dowload_statuscard(string position){
    std::ifstream archive;
    archive.open("Disk.txt",std::ios::in);
    if(archive.fail()){
        std::cout<<"Can't open the disk";
    }
    std::string text;

    std::string information;

    while (getline(archive, text)) {
        information += text;
        information += "\n";
    }
    archive.close();
    int length = information.length();
    int raw = 0;
    int column = 0;
    std::string changed_text;
    for(int i= 0 ;i <= length;i++){

        std::string parenthesis;
        parenthesis +=information[i];
        std::string position2 = std::to_string(raw) + ":" +std::to_string(column);
        if(position == position2 ){
            changed_text += "f";
            position = "find it";
        }
        else{
            changed_text += parenthesis;
        }
        if(column == 10){
            raw += 1;
            column = 0;
            continue;
            std::cout<<raw<<std::endl;
        }
        if(parenthesis == "]"){
            column += 1;
        }
    }
    std::ofstream archive2;
    archive2.open("Disk.txt",std::ios::out);
    archive2<<changed_text;
    archive2.close();
}
