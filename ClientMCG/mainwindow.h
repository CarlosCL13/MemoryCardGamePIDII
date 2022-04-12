#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <iostream>
#include <QPushButton>
#include <QRegularExpression>


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

    void addplayersname(QString name1, QString name2);
    void setimagecard(string encoded, QPushButton* button);

public slots:
    void onReadyRead();
    void onSendButtonPressed(QString messagge);
    void uncovered_card();



private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
};
#endif // MAINWINDOW_H
