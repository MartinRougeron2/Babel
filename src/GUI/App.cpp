/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/

#include <QtGui>
#include "GUI/App.h"

App::App(QWidget *parent) : QWidget(parent), login
{
    setWindowTitle("Babel");
}

void App::call(User contact_to_call)
{

}

void App::acceptCall(User contact_from)
{

}

void App::refuseCall()
{

}

void App::dismiss()
{

}

void App::addContactToCall(User contact_to_add)
{

}

void App::removeContactToCall(User contact_to_remove)
{

}

void App::addContact(User contact_to_add)
{
    this->contact_list.append(
        new Contact(contact_to_add.username, contact_to_add.address, true)
    );


}

void App::removeContact(User contact_to_remove)
{

}

void App::fetchUsers()
{

}

void App::login()
{
    // if (send(username, password))
    // this->app_state = Menu
}

void App::update()
{
    switch(this->app_state) {
        case ToLog:
            loginui->show();
            break;
    }
}
