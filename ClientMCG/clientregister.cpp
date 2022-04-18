#include "clientregister.h"
#include "ui_clientregister.h"
#include "mainwindow.h"

ClientRegister::ClientRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientRegister)
{
    ui->setupUi(this);
    connect(this, &ClientRegister::namesignal, this, &ClientRegister::onSignalEmited);
}

ClientRegister::~ClientRegister()
{
    delete ui;
}

void ClientRegister::onSignalEmited(){
    ui->startButton->setEnabled(true);
}
void ClientRegister::on_startButton_clicked()
{
    name1 = ui->name1->text();
    name2 = ui->name2->text();
    MainWindow* window = new MainWindow;
    window->addplayersname(name1, name2);
    this->close();
    window->show();
}


void ClientRegister::on_name1_editingFinished(){
    cout << "First name get it" << endl;
}


void ClientRegister::on_name2_editingFinished(){
    emit namesignal();
}


void ClientRegister::on_name2_returnPressed(){
    emit namesignal();
}

