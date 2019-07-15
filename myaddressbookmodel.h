#ifndef MYADDRESSBOOKMODEL_H
#define MYADDRESSBOOKMODEL_H

#include <QAbstractTableModel>
#include <vector>

class MyAddressBookModel: public QAbstractTableModel
{
public:
    MyAddressBookModel(QObject *parent);
    std::vector<QString> firstNames;
    std::vector<QString> lastNames;
    std::vector<QString> phoneNumbers;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void openFile(QString filePath);
    QString getPhoneNumber(int index);
    void filterList(QString num);

private:
    std::vector<QString> filteredFirstName;
    std::vector<QString> filteredLastName;
    std::vector<QString> filteredphoneNumber;
    std::vector<int> filteredIndex;
};

#endif // MYADDRESSBOOKMODEL_H
