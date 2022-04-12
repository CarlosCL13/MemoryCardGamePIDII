#ifndef CLIENTREGISTER_H
#define CLIENTREGISTER_H

#include <QMainWindow>

namespace Ui {
class ClientRegister;
}

class ClientRegister : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientRegister(QWidget *parent = nullptr);
    ~ClientRegister();
    QString name1;
    QString name2;

private slots:
    void on_startButton_clicked();

private:
    Ui::ClientRegister *ui;
};

#endif // CLIENTREGISTER_H
