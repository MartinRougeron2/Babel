/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#ifndef CHAT_MESSAGE_HPP
    #define CHAT_MESSAGE_HPP

    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <iostream>
    #include <list>
    #include <memory>
    #include <set>
    #include <vector>
    #include <utility>
    #include <algorithm>
    #include <string>
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>

    #include "Signals.hpp"
    #include "Logs.hpp"
    #include "Asqlite3.hpp"

    #define TCP_PORT 2000
    #define EMPTY "__EMPTY__"

    using boost::asio::ip::tcp;

    class Session : public std::enable_shared_from_this<Session>
    {
        public:
            Session(boost::asio::io_service &);

            tcp::socket &get_socket();

            void start();
            void handle_read(std::shared_ptr<Session> &, const boost::system::error_code &, std::size_t);

            typedef bool (Session::*function_type)(struct User);

            std::map<std::string, function_type> mapped = {
                { "/login", &Session::login },
                { "/logout", &Session::logout },
                { "/join", &Session::join },
                { "/leave", &Session::leave },
                { "/call", &Session::call },
                { "/ping", &Session::ping },
                { "/exit", &Session::exit }
            };

            bool login(struct User);
            bool logout(struct User);
            bool join(struct User);
            bool leave(struct User);
            bool call(struct User);
            bool ping(struct User);
            bool exit(struct User);

            User decoder(std::string, User);
            User set_new_user();

        private:
            enum
            {
                max_length = 1024
            };

            tcp::socket socket;
            char data[max_length];
            std::vector<std::string> users;
            Asqlite3 database;
            void close_socket();

            std::string current_command;
            std::string current_arguments;
    };

    class Server
    {
        public:
            Server(boost::asio::io_service &, short);

            void handle_accept(std::shared_ptr<Session>, const boost::system::error_code &);

        private:
            boost::asio::io_service &ios;
            tcp::acceptor acceptor;
    };

#endif // CHAT_MESSAGE_HPP
