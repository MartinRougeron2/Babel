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

#include "../common/User.h"
#include "Contact.h"

class App : public QWidget {
    Q_OBJECT
    public:
        App();


        void call(Contact contact_to_call);
        void acceptCall(Contact contact_from);
        void refuseCall();
        void dismiss();

        void addContactToCall(Contact contact_to_add);
        void removeContactToCall(Contact contact_to_remove);

        void addContact(Contact contact_to_add);
        void removeContact(Contact contact_to_remove);

        void fetchUsers();

        void login();

    private:
        User user;
        QList<Contact> contact_list; // selected
        QList<User> all_users; // all
        AppState app_state = ToLog;

        QLineEdit *search_name;

        QLineEdit *username;
        QLineEdit *password;

        void update();

}

#endif //BABEL_APP_H
