#include "clientregister.h"
#include "ui_clientregister.h"
#include "mainwindow.h"

ClientRegister::ClientRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientRegister)
{
    ui->setupUi(this);
}

ClientRegister::~ClientRegister()
{
    delete ui;
}


void ClientRegister::on_startButton_clicked()
{
    name1 = ui->name1->text();
    name2 = ui->name2->text();
    if(name1 != "" && name1 != ""){
        MainWindow* window = new MainWindow;
        window->addplayersname(name1, name2);
        this->close();
        window->show();
    }else{
        name1 = "Player 1";
        name2 = "PLayer 2";
        MainWindow* window = new MainWindow;
        window->addplayersname(name1, name2);
        this->close();
        window->show();
    }

}

