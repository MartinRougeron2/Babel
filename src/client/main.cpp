/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include <QtGui>
#include <QApplication>
#include "GUI/App.h"
#include "client/protocol/ClientUdp.hpp"

using boost::asio::ip::tcp;

int main(int argc, char **argv)
{

    if (argc != 2) {
        std::cerr <<  "No ip adress provided" << std::endl;
        return 84;
    }
    QApplication app(argc, argv);
    App main_app(nullptr, std::string(argv[1]));

    main_app.show(); //show the widget and its children
    return app.exec(); // execute the application
}
