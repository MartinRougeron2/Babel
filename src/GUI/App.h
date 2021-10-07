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

enum loginCode {SUCCESS, USER_NOT_EXIST, BAD_PASSWORD};
//TODO REMOVEAND USE SQLITE

class App : public QWidget
{
    Q_OBJECT

    public:
        App(QWidget *parent=NULL);
        virtual ~App() {};
        std::vector<User> fetchContact();
        bool checkUser(std::string usr);

    public slots:

        void call(User user_to_call);
        void acceptCall();
        void refuseCall();
        void dismiss();

        void addContactToCall(User user_to_add);
        void removeContactToCall(User user_to_remove);

        void addContact(User user_to_add);
        void removeContact(User user_to_remove);

        User getUser() const { return this->user;};

        loginCode login(std::string username, std::string password);
        void update();

    private:
        enum AppState {ToLog, Menu_};
        User user = {"martin", "cringe", "127.0.0.1", 1};
        AppState app_state = ToLog;

        QLineEdit *search_name;
        QWidget *loginui;
        QWidget *usermenu;

};

#endif //BABEL_APP_H
