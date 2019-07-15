#ifndef PHONEWINDOW_H
#define PHONEWINDOW_H

#include <QMainWindow>
#include "myaddressbookmodel.h"

namespace Ui {
class PhoneWindow;
}

class PhoneWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PhoneWindow(QWidget *parent = nullptr);
    ~PhoneWindow();

private slots:
    void on_actionOpen_an_Address_Book_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_actionExit_triggered();

    void on_dialNum1_clicked();

    void on_dialNum2_clicked();

    void on_dialNum3_clicked();

    void on_dialNum4_clicked();

    void on_dialNum5_clicked();

    void on_dialNum6_clicked();

    void on_dialNum7_clicked();

    void on_dialNum8_clicked();

    void on_dialNum9_clicked();

    void on_dialNumAterisk_clicked();

    void on_dialNum0_clicked();

    void on_dialNumHash_clicked();

    void on_CallButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::PhoneWindow *ui;
    MyAddressBookModel *myModel;

    QString phoneNumber;
    QString backupNumber;
    bool isLoaded = false;
    QString fileName;
    void FormatNumber(QString);
};

#endif // PHONEWINDOW_H
