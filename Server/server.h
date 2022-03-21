#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

#include <string.h>
#include <string>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

    void send_message(string msg);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Server *ui;
};
#endif // SERVER_H
