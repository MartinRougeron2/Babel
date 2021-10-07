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

void App::acceptCall()
{
    //TODO ACCEPT CALL
}

void App::refuseCall()
{
    //TODO REFUSE CALL
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
    //TODO ADD CONTACT TO DB
}

void App::removeContact(User contact_to_remove)
{
    //TODO REMOVE CONTACT FROM DB
}

bool App::checkUser(std::string username)
{
    //TODO CHECK IF USER EXIST
    return true;
}

std::vector<User> App::fetchContact()
{
    std::vector<User> linkeds;
    linkeds.push_back({"dd", "dd", "dd", 0});
    linkeds.push_back({"YOJ", "dd", "dd", 1});
    linkeds.push_back({"Vat", "dd", "dd", 2});
    //TODO GET LINKED
    return linkeds;
}

loginCode App::login(std::string username, std::string password)
{
    //TODO LOGIN
    this->app_state = Menu_;
    this->user = {username, password, "", 0};
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
