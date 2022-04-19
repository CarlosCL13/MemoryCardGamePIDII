#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <iostream>
#include <QPushButton>
#include <QRegularExpression>
#include <QTimer>
#include <QMessageBox>

#pragma once


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    static MainWindow *instance;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getInstance();
    QPushButton* currentCard;
    QPushButton* previousCard;
    QTimer *timer=new QTimer();
    QMessageBox msgBox;
    bool first_card;
    int score1 = 0;
    int score2 = 0;
    int pairsofcards = 20;



public slots:
    void onReadyRead();
    void onSendButtonPressed(QString messagge);
    void uncovered_card();
    void startGame();
    void addplayersname(QString name1, QString name2);
    void setimagecard1(QString encoded, QPushButton* button);
    void setimagecard2(QString encoded, QPushButton* button);
    void partial_result1();
    void partial_result2();
    void final_result();
    void restartCards();



private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
};
#endif // MAINWINDOW_H
