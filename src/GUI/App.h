/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/


#ifndef BABEL_APP_H
#define BABEL_APP_H

#include <QWidget>
#include <QtWidgets>
#include <QList>
#include <QLineEdit>
#include <string>
#include "include/common/User.h"
#include "Contact.h"

enum loginCode {SUCCESS, USER_NOT_EXIST, BAD_PASSWORD};
//TO REMOVEAND USE SQLITE

class App : public QWidget
{
    Q_OBJECT

    public:
        App(QWidget *parent=NULL);
        virtual ~App() {};

    public slots:

        void call(User user_to_call);
        void acceptCall(User user_from);
        void refuseCall();
        void dismiss();

        void addContactToCall(User user_to_add);
        void removeContactToCall(User user_to_remove);

        void addContact(User user_to_add);
        void removeContact(User user_to_remove);

        void fetchUsers();

        User getUser() const { return this->user;};

        loginCode login(std::string username, std::string password);
        void update();

    private:
        User user = {"martin", "cringe", "127.0.0.1"};
        QList<Contact *> contact_list; // selected
        QList<User> all_users; // all
        AppState app_state = ToLog;

        QLineEdit *search_name;
        QWidget *loginui;
        QWidget *usermenu;

};

#endif //BABEL_APP_H
