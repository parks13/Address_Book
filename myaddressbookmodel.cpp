#include "myaddressbookmodel.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>

MyAddressBookModel::MyAddressBookModel(QObject *parent):QAbstractTableModel (parent)
{

}

int MyAddressBookModel::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}

int MyAddressBookModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant MyAddressBookModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        switch(index.column())
        {
            case 0: // first name
                return firstNames.at(filteredIndex[index.row()]);
            case 1: // last name
                return lastNames.at(filteredIndex[index.row()]);
            case 2: // phone number
                return phoneNumbers.at(filteredIndex[index.row()]);
        }
    }
    return QVariant();
}

void MyAddressBookModel::openFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QTextStream in(&file);

    firstNames.clear();
    lastNames.clear();
    phoneNumbers.clear();

    for (int i = 0; !in.atEnd(); i++)
    {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (i == 0) continue;

        firstNames.push_back(fields[0]);
        lastNames.push_back(fields[1]);
        phoneNumbers.push_back(fields[7]);

        filteredIndex.push_back(i-1); // fixed bug
    }

    file.close();

    emit layoutChanged();
}

QString MyAddressBookModel::getPhoneNumber(int index)
{
    return phoneNumbers.at(filteredIndex[index]);
}

void MyAddressBookModel::filterList(QString num)
{
    filteredIndex.clear();

    // Filter by phone number and first and last names
    for (int i = 0; i < phoneNumbers.size(); i++)
    {
        if (phoneNumbers[i].startsWith(num)) // Filter by number
            filteredIndex.push_back(i);

        else // Filter by first and last names
        {
            // Clear digits and characters that are not linked to alphabets from num
            QString number;
            for (int j = 0; j < num.length(); j++)
            {
                if (num[j] != '1' && num[j] != '0' && num[j] != '*' && num[j] != '#' && num[j] != '-')
                    number += num[j];
            }

            // Go through each numbers and its corresponding characters
            bool matchFound = false;
            bool searchLast = false;
            bool searchFirst = false;
            QString matchString = "";
            for (int j = 0; j < number.length(); j++)
            {
                QString alphabet; // Set the correct alphabet string
                if (number[j] == '2') // ABC
                    alphabet = "ABC";
                if (number[j] == '3') // DEF
                    alphabet = "DEF";
                if (number[j] == '4') // GHI
                    alphabet = "GHI";
                if (number[j] == '5') // JKL
                    alphabet = "JKL";
                if (number[j] == '6') // MNO
                    alphabet = "MNO";
                if (number[j] == '7') // PQRS
                    alphabet = "PQRS";
                if (number[j] == '8') // TUV
                    alphabet = "TUV";
                if (number[j] == '9') // WXYZ
                    alphabet = "WXYZ";

                // Check firstNames then lastNames if not found
                for (int k = 0; k < alphabet.length(); k++)
                {
                    QString tmpString = matchString + alphabet[k];
                    if (firstNames[i].startsWith(tmpString, Qt::CaseInsensitive) && !searchLast)
                    {
                        matchFound = true;
                        searchFirst = true;
                        matchString += alphabet[k];
                        break;
                    }
                    else if (lastNames[i].startsWith(tmpString, Qt::CaseInsensitive) && !searchFirst)
                    {
                        matchFound = true;
                        searchLast = true;
                        matchString += alphabet[k];
                        break;
                    }
                    else if (k == (alphabet.length()-1))
                        matchFound = false;
                }
                std::cout << matchString.toStdString() << std::endl;

                if (!matchFound)
                    break;
            }
            if (matchFound)
                filteredIndex.push_back(i);
        }
    }
    emit layoutChanged();
}
