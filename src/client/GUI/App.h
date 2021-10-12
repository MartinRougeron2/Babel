/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/


#ifndef BABEL_APP_H
#define BABEL_APP_H

class UserMenu;

#include <QWidget>
#include <QtWidgets>
#include <QList>
#include <QLineEdit>
#include <string>
#include "common/User.h"

enum loginCode {SUCCESS, USER_NOT_EXIST, BAD_PASSWORD};
//TODO REMOVEAND USE SQLITE

class App : public QWidget
{
    Q_OBJECT

    public:
        App(QWidget *parent=NULL);
        virtual ~App() {};
        std::vector<UserApp> fetchContact() const;
        bool checkUser(std::string usr);
        void hangup();
        UserApp getUser(std::string username) const;
        std::vector<UserApp> getUserInCall() const;
        void updateCall() const;

    public slots:

        void call(UserApp user_to_call);
        void acceptCall();
        void refuseCall();
        void dismiss();

        void addContactToCall(UserApp user_to_add);
        void removeContactToCall(UserApp user_to_remove);

        void addContact(UserApp user_to_add);
        void removeContact(UserApp user_to_remove);

        UserApp getContext() const { return this->user;};

        loginCode login(std::string username, std::string password);
        void update();

    private:
        enum AppState {ToLog, Menu_};
        UserApp user = {"martin", "cringe", "127.0.0.1", 1};
        AppState app_state = ToLog;

        QLineEdit *search_name;
        QWidget *loginui;
        UserMenu *usermenu;

};

#endif //BABEL_APP_H