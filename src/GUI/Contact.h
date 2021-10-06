/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#ifndef BABEL_CONTACT_H
#define BABEL_CONTACT_H

#include "constants.h"
#include <include/common/User.h>

#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QGridLayout>
#include <QtWidgets>
#include <QWidget>


class Contact : public QWidget {
    Q_OBJECT

    // virtual ~App() {};
public:

        Contact(std::string username, std::string address = "", bool in_list =
            false);
        User call();
        User addToList();
        void removeFromList();
        void removeFromCall();

        QPushButton *get_call();
        QPushButton *get_remove_from_call();
        QPushButton *get_add_to_list();
        QPushButton *get_remove_from_list();

        QGridLayout *mainLayout;

        void setContext(Context newContext);

    private:

        void update();
        void resetLayout() const;
        QLabel *name_label;
        User user;

        QPushButton *call_btn;
        QPushButton *remove_from_call_btn;
        QPushButton *add_to_list_btn;
        QPushButton *remove_from_list_btn;

        QGridLayout *contactLayout;

        Context contact_context;
        ContactState contact_state;

        QWidget login;
};

#endif //BABEL_CONTACT_H
