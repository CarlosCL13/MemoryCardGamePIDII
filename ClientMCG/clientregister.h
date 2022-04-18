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

signals:
    void namesignal();


private slots:
    void on_startButton_clicked();
    void onSignalEmited();

    void on_name1_editingFinished();

    void on_name2_editingFinished();

    void on_name2_returnPressed();

private:
    Ui::ClientRegister *ui;
};

#endif // CLIENTREGISTER_H
