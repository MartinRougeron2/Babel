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

#include "Call.h"

class UserMenu : public QWidget
{
    Q_OBJECT
    public:
        UserMenu(QWidget *parent = 0);

    public slots:
        void addContact();
        void removeContact();
        void call();
        void setSelectioned(User usr);
        Call *getCallW() const { return this->callWidget;};

    private:
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

        ModifyPopup *dialog;
        User selection = {"", "", "", -1};

        App *app;
};



#endif //USERMENU_H
