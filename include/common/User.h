/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** User
*/

#include "standard.h"

#ifndef BABEL_USER_H
#define BABEL_USER_H

struct UserApp {
    std::string username;
    std::string address;
    std::string password;
    int id;

    bool operator<(UserApp &other)
    {
        return other.username < this->username;
    }
    User(std::string username_="",
         std::string address_="",
         std::string password_="") :
         username(username_),
         address(address_),
         password(password_)
         {
         }

    UserApp(std::string username_="", std::string address_="", std::string password_="", int id_=-1) :
        username(username_),
        address(address_),
        password(password_),
        id(id_)
        {
        }

};


#endif //BABEL_USER_H
