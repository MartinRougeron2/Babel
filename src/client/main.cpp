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
    // boost::asio::io_service ios;
    // Sound::RecorderPlayer player;
    // ClientUdp voiceClient = ClientUdp("127.0.0.1", ios, player);


   QApplication app(argc, argv);
   App main_app;

    main_app.show(); //show the widget and its children
    return app.exec(); // execute the application
}
