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

std::vector<User> App::getUserInCall() const
{
    //TODO RETURN USER IN CONTEXT CALL;
    return fetchContact();
}

User App::getUser(std::string username) const
{
    //TODO RETURN USER WITH USERNAME;
    return {"user", "password", "address", 5};
}

void App::call(User contact_to_call)
{
    //TODO CREATE CALL THEN ADD USER TO CALL
}

void App::hangup()
{
    //TODO HANGUP
}

void App::acceptCall()
{
    //TODO ACCEPT CALL
    updateCall();
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
    //TODO ADD CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN YOUR CONTACT
}

void App::removeContactToCall(User contact_to_remove)
{
    //TODO REMOVE CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN THE CALL
}

void App::addContact(User contact_to_add)
{
    //TODO ADD CONTACT TO DB
    //ALREADY IN UR CONTACT ?
}

void App::removeContact(User contact_to_remove)
{
    //TODO REMOVE CONTACT FROM DB
    //NOT IN YOUR CONTACT (should not be called)
}

bool App::checkUser(std::string username)
{
    //TODO CHECK IF USER EXIST
    return true;
}

std::vector<User> App::fetchContact() const
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
            this->usermenu = new UserMenu(this);
            break;
    }
}

void App::updateCall() const
{
    usermenu->getCallW()->updateCall();
}
