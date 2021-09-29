/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/


#ifndef USERMENU_H
#define USERMENU_H

#include <QWidget>
#include <QtWidgets>
#include <QMap>

#include "ModifyPopup.h"

class UserMenu : public QWidget
{
    Q_OBJECT
    public:
        UserMenu(QWidget *parent = 0);
        enum Mode { NavigationMode, AddingMode, EditingMode };

    public slots:
                void addContact();
        void editContact();
        void submitContact();
        void cancel();
        void removeContact();
        void findContact();
        void next();
        void previous();
        void saveToFile();
        void loadFromFile();
        void exportAsVCard();

    private:
        void updateInterface(Mode mode);

        QPushButton *addButton;
        QPushButton *editButton;
        QPushButton *removeButton;
        QPushButton *findButton;
        QPushButton *submitButton;
        QPushButton *cancelButton;
        QPushButton *nextButton;
        QPushButton *previousButton;
        QPushButton *loadButton;
        QPushButton *saveButton;
        QPushButton *exportButton;
        QLineEdit *nameLine;
        QTextEdit *addressText;

        QMap<QString, QString> contacts;
        ModifyPopup *dialog;
        QString oldName;
        QString oldAddress;
        Mode currentMode;
};



#endif //USERMENU_H
