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
#include "common/User.hpp"
#include "client/TCP.hpp"

enum loginCode {SUCCESS, USER_NOT_EXIST, NOT_CONNECTED, BAD_PASSWORD};
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

        TCP *getTcp() const { return this->client;};
    public slots:

        void call(UserApp user_to_call);
        void acceptCall();
        void refuseCall();

        void addContactToCall(UserApp user_to_add);
        void removeContactToCall(UserApp user_to_remove);

        bool addContact(std::string user_to_add);
        bool removeContact(std::string user_to_remove);

        UserApp getContext() const { return this->user;};

        loginCode login(std::string username, std::string password);
        void update();

        static UserApp convertUserFromString(std::string username);

    private:
        enum AppState {ToLog, Menu_};
        UserApp user = {"martin", "cringe", "127.0.0.1", 1};
        AppState app_state = ToLog;

        QLineEdit *search_name;
        QWidget *loginui;
        UserMenu *usermenu;
        TCP *client;

};

#endif //BABEL_APP_H
