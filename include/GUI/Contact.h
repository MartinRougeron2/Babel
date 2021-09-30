/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#ifndef BABEL_CONTACT_H
#define BABEL_CONTACT_H

#include "constants.h"

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QGridLayout>


class Contact {
    Q_OBJECT

    public:

        Contact(std::string username, std::string address = "", bool in_list =
            false);
        std::string call();
        QString addToList();
        void removeFromList();
        void removeFromCall();

        QPushButton get_call();
        QPushButton get_remove_from_call();
        QPushButton get_add_to_list();
        QPushButton get_remove_from_list();

        void setContext(Context newContext);

    private:

        void update();

        QString username;
        std::string address;

        QPushButton *call;
        QPushButton *remove_from_call;
        QPushButton *add_to_list;
        QPushButton *remove_from_list;

        QGridLayout *contactLayout;

        Context contact_context;
        State contact_state;
};

#endif //BABEL_CONTACT_H
