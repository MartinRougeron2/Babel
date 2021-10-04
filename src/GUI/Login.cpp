/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Login
*/

#include "GUI/Login.hpp"

Login::Login()
{
    this->username_info = new QLabel("username:");
    this->username_edit = new QLineEdit("username");
    //SET MAX USERNAME LEN
    this->username_error = new QLabel("error username");
    this->username_error->setStyleSheet("font-weight: bold; color: red");
    this->password_info = new QLabel("password:");
    this->password_edit = new QLineEdit("password");
    this->password_error = new QLabel("error password");
    this->password_error->setStyleSheet("font-weight: bold; color: red");
    this->login_button = new QPushButton("LOGIN");

    connect(login_button, SIGNAL(clicked()), this, SLOT(proceed_login));
    update();
}

Login::~Login()
{
}

void Login::proceed_login()
{
    //proceed
}

