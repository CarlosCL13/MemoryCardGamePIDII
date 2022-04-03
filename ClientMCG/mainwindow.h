#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setimagecard(string encoded);

public slots:
    void onReadyRead();
    void onSendButtonPressed(QString messagge);
    //void onLoginButtonPressed();



private slots:
    void on_card1_clicked();

    void on_card2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
};
#endif // MAINWINDOW_H
