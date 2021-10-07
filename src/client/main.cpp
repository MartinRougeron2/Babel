/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include <QtGui>
#include <QApplication>
#include "GUI/App.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    App main_app;
    // boost::asio::io_service io_service;

    // signals::handler();
    // TCP client_tcp = TCP();
    // try
    // {
    //     tcp::resolver resolver(io_service);
    //     auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
    //     chat_client c(io_service, endpoint_iterator);

    //     std::thread t([&io_service](){ io_service.run(); });

    //     char line[chat_message::max_body_length + 1];

    //     while (std::cin.getline(line, chat_message::max_body_length + 1))
    //     {
    //         chat_message msg;
    //         msg.body_length(std::strlen(line));
    //         std::memcpy(msg.body(), line, msg.body_length());
    //         msg.encode_header();
    //         c.write(msg);
    //     }
    //     c.close();
    //     t.join();
    // }
    // catch (std::exception& e)
    // {
    //     std::cerr << "Exception: " << e.what() << "\n";
    // }

    main_app.show(); //show the widget and its children
    return app.exec(); // execute the application
}
