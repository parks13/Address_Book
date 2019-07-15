#include "phonewindow.h"
#include "ui_phonewindow.h"

#include <QFileDialog>
#include <iostream>
#include <QMessageBox>

PhoneWindow::PhoneWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PhoneWindow),
    myModel(new MyAddressBookModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(myModel);

    phoneNumber = "";
}

PhoneWindow::~PhoneWindow()
{
    delete ui;
}

void PhoneWindow::on_actionOpen_an_Address_Book_triggered()
{
    fileName = QFileDialog::getOpenFileName(this,
                                         tr("Open Address Book"), "",
                                         tr("Address Book (*.csv);;AllFiles (*)"));
    myModel->openFile(fileName);
    isLoaded = true;
}

void PhoneWindow::on_tableView_clicked(const QModelIndex &index)
{
    // Set the phone number to the phoneNumber object
    phoneNumber = myModel->getPhoneNumber(index.row());
    ui->phoneNumLabel->setText(phoneNumber);
}

void PhoneWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

// Add number 1
void PhoneWindow::on_dialNum1_clicked()
{
    FormatNumber("1");
}

// Add number 2
void PhoneWindow::on_dialNum2_clicked()
{
    FormatNumber("2");
}

// Add number 3
void PhoneWindow::on_dialNum3_clicked()
{
    FormatNumber("3");
}

// Add number 4
void PhoneWindow::on_dialNum4_clicked()
{
    FormatNumber("4");
}

// Add number 5
void PhoneWindow::on_dialNum5_clicked()
{
    FormatNumber("5");
}

// Add number 6
void PhoneWindow::on_dialNum6_clicked()
{
    FormatNumber("6");
}

// Add number 7
void PhoneWindow::on_dialNum7_clicked()
{
    FormatNumber("7");
}

// Add number 8
void PhoneWindow::on_dialNum8_clicked()
{
    FormatNumber("8");
}

// Add number 9
void PhoneWindow::on_dialNum9_clicked()
{
    FormatNumber("9");
}

// Add * sign
void PhoneWindow::on_dialNumAterisk_clicked()
{
    FormatNumber("*");
}

// Add number 0
void PhoneWindow::on_dialNum0_clicked()
{
    FormatNumber("0");
}

// Add # sign
void PhoneWindow::on_dialNumHash_clicked()
{
    FormatNumber("#");
}

// Call the number entered
void PhoneWindow::on_CallButton_clicked()
{
    if (phoneNumber.isEmpty()) // Extra function, mimics the daily phone feature where call button calls last recent number
        phoneNumber = backupNumber;

    QMessageBox msgBox;
    msgBox.setText("Calling " + phoneNumber);
    msgBox.setWindowTitle("Calling...");
    msgBox.exec();

    // Clear out phone number string
    backupNumber = phoneNumber;
    phoneNumber.clear();

    myModel->filterList(phoneNumber);
    ui->phoneNumLabel->setText(phoneNumber);
}

// Delete the phone number by 1 character or 2 if "-" is present
// Also delete the alphabets as number gets deleted
void PhoneWindow::on_deleteButton_clicked()
{
    // Delete digits from the right
    if (phoneNumber.length() > 0)
    {
        phoneNumber.chop(1);

        // Delete the dash (-) in a phoneNumber string if present
        if (phoneNumber.length() > 0 && phoneNumber.back() == "-")
            phoneNumber.chop(1);
    }
    myModel->filterList(phoneNumber);

    ui->phoneNumLabel->setText(phoneNumber);
}

// Function to format and display phone number
void PhoneWindow::FormatNumber(QString num)
{
    // Manipulate the phoneNubmer string by checking its current number of digits entered
    if (phoneNumber.length() < 12)
    {
        if (phoneNumber.length() == 3 || phoneNumber.length() == 7)
            phoneNumber.append("-" + num);
        else
            phoneNumber.append(num);
    }

    myModel->filterList(phoneNumber);

    // Display the formatted phoneNumber string to the label
    ui->phoneNumLabel->setText(phoneNumber);
}

