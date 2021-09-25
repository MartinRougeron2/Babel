/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include <QtGui>
#include "../../include/babel.hpp"
#include "../../include/GUI/UserMenu.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    UserMenu menu;

    menu.show(); //show the widget and its children
    return app.exec(); // execute the application
}
