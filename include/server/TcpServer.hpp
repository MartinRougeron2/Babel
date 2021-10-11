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
    #include "Protocol.hpp"
    #include "UdpServer.hpp"


    #define TCP_PORT 2000
    #define EMPTY "__EMPTY__"

    using boost::asio::ip::tcp;

    class TcpSession : public std::enable_shared_from_this<TcpSession>
    {
        public:
            TcpSession(boost::asio::io_service &, UdpServer *copy);

            tcp::socket &get_socket();

            void start();
            void handle_read(std::shared_ptr<TcpSession> &, const
                boost::system::error_code &, std::size_t);

            typedef bool (TcpSession::*function_type)(std::string, struct User);

            std::map<std::string, function_type> mapped = {
                { "/login", &TcpSession::login },
                { "/logout", &TcpSession::logout },
                { "/join", &TcpSession::join },
                { "/leave", &TcpSession::leave },
                { "/call", &TcpSession::call },
                { "/ping", &TcpSession::ping },
                { "/exit", &TcpSession::close_server }
            };

            bool login(std::string, struct User);
            bool logout(std::string, struct User);
            bool join(std::string, struct User);
            bool leave(std::string, struct User);
            bool call(std::string, struct User);
            bool ping(std::string, struct User);
            bool close_server(std::string, struct User);

            void display(User);
            User C_user_to_user(C_User);
            Commands C_command_to_commands(C_Commands);

            S_Protocol decode(std::string);
            bool send(char *);
            char *set_string(char *);

        private:
            enum
            {
                max_length = 1024
            };
            tcp::socket socket;

            Protocol *recv;
            char buffer[max_length];

            User recv_user;
            Commands recv_commands;
            std::vector<std::string> users;
            Asqlite3 database;
            void close_socket();
            UdpServer *voiceServer;
    };

    class TcpServer
    {
        public:
            TcpServer(boost::asio::io_service &, short);

            void handle_accept(std::shared_ptr<TcpSession>, const
                boost::system::error_code &);

        private:
            boost::asio::io_service &ios;
            tcp::acceptor acceptor;
            UdpServer *voiceServer;
    };

#endif // CHAT_MESSAGE_HPP
