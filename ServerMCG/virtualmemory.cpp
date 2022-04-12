#include "virtualmemory.h"
#include "mainwindow.h"

VirtualMemory *VirtualMemory::instance = nullptr;

VirtualMemory* VirtualMemory::getInstance() {
    if (instance == nullptr){
        instance = new VirtualMemory;
    }
    return instance;
}

VirtualMemory::VirtualMemory()
{}

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
            cout << "Can't open" << endl;
            exit(1);
        }
         for(int i = 0;i < 4;i++){
             //i++;
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
                        //j++;
                    }

                    information += "&";
                    archive<<information;
                    //contador += 1;
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
            std::cout<<"ERROR";
        }
        std::string text;
        int row = 0;
        while (getline(archive, text)) {
            int column = 0;
            for(int i= 0 ;i <= text.length();i++){
                std::string letter;
                letter += text[i];
                std::string position2 = std::to_string(row) + ":" +std::to_string(column);
                if(position == position2){
                    std::string typeCard;
                    int j = i;
                    while(true){
                        std::string letter2;
                        letter2 += text[j];
                        if (letter2 == "&"){
                            //std::cout << typeCard << std::endl;
                            return typeCard;
                        }
                        else{
                            typeCard += letter2 ;
                            j += 1;
                        }
                    }
                }
                if (letter == "&"){
                    column += 1;
                }
            }
            row += 1;
        }
        archive.close();
        return 0;

}
