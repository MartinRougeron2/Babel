/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** babel
*/

#include <QtGui>
#include "App.h"
#include "Login.h"
#include "UserMenu.h"
#include <iostream>

App::App(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Babel");
    this->client = new TCP();
    update();
}

std::vector<UserApp> App::getUserInCall() const
{
    //TODO RETURN USER IN CONTEXT CALL;
    return fetchContact();
}

UserApp App::getUser(std::string username) const
{
    //TODO RETURN USER WITH USERNAME;
    return {"user", "address", "password", 5};
}

void App::call(UserApp contact_to_call)
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

void App::addContactToCall(UserApp contact_to_add)
{
    //TODO ADD CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN YOUR CONTACT
}

void App::removeContactToCall(UserApp contact_to_remove)
{
    //TODO REMOVE CONTACT TO CONTEXT USER CALL
    //NEED TO CHECK IF USER IS IN THE CALL
}

void App::addContact(UserApp contact_to_add)
{
    //TODO ADD CONTACT TO DB
    //ALREADY IN UR CONTACT ?
}

void App::removeContact(UserApp contact_to_remove)
{
    //TODO REMOVE CONTACT FROM DB
    //NOT IN YOUR CONTACT (should not be called)
}

bool App::checkUser(std::string username)
{
    //TODO CHECK IF USER EXIST
    return true;
}

std::vector<UserApp> App::fetchContact() const
{
    std::vector<struct UserApp> linkeds;
    linkeds.push_back(UserApp("dd", "dd", "dd", 0));
    linkeds.push_back(UserApp("yoj", "dd", "dd", 1));
    linkeds.push_back(UserApp("eedede", "dd", "dd", 2));
    //TODO GET LINKED
    return linkeds;
}

loginCode App::login(std::string username, std::string password)
{
    //TODO LOGIN
    this->app_state = Menu_;
    this->user = UserApp(username, "", password, 0);
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
