/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/

#include <QtGui>
#include "App.h"
#include "Login.hpp"
#include "UserMenu.h"
#include <iostream>

App::App(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Babel");
    update();
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

loginCode App::login(std::string username, std::string password)
{
    //TODO LOGIN
    this->app_state = Menu_;
    this->user = {username, password, ""};
    return SUCCESS;
}

void App::update()
{
    switch(this->app_state) {
        case ToLog:
            loginui = new Login(this);
            break;
        case Menu_:
            delete loginui;
            usermenu = new UserMenu(this);
            break;
    }
}
