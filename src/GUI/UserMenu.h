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
#include <QList>

#include "ModifyPopup.h"
#include "Call.hpp"

class UserMenu : public QWidget
{
    Q_OBJECT
    public:
        UserMenu(QWidget *parent = 0);
        enum Mode { NavigationMode, AddingMode, EditingMode };

    public slots:
        void addContact();
        void removeContact();
        void call();
        void setSelectioned(User usr);

    private:
        void updateInterface(Mode mode);
        void fetchContact();
        ContactLabel *findLabelWithId(int);

        QPushButton *addButton;
        QPushButton *removeButton;
        QPushButton *callButon;
        QLineEdit *nameLine;
        QList<ContactLabel *> contactDraw = {};
        Call *callWidget;

        QGridLayout *mainLayout;
        QVBoxLayout *contactLayout;

        QMap<QString, QString> contacts;
        ModifyPopup *dialog;
        QString oldName;
        QString oldAddress;
        Mode currentMode;
        User selection = {"", "", "", -1};

        App *app;
};



#endif //USERMENU_H
