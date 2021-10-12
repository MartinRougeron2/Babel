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
            TcpSession(boost::asio::io_service &, UdpServer *copy, std::mutex *copyMtx);

            tcp::socket &getSocket();

            void start();
            void handleRead(std::shared_ptr<TcpSession> &, const
                boost::system::error_code &, std::size_t);

            typedef bool (TcpSession::*function_type)(std::string, struct UserApp);

            std::map<std::string, function_type> mapped = {
                { "/login", &TcpSession::login },
                { "/logout", &TcpSession::logout },
                { "/join", &TcpSession::join },
                { "/leave", &TcpSession::leave },
                { "/call", &TcpSession::call },
                { "/ping", &TcpSession::ping },
                { "/exit", &TcpSession::close_server }
            };

            bool login(std::string, struct UserApp);
            bool logout(std::string, struct UserApp);
            bool join(std::string, struct UserApp);
            bool leave(std::string, struct UserApp);
            bool call(std::string, struct UserApp);
            bool ping(std::string, struct UserApp);
            bool close_server(std::string, struct UserApp);

            void display(UserApp);
            UserApp C_user_to_user(C_User);
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

            UserApp recvUser;
            Commands recvCommands;
            std::vector<std::string> users;
            Asqlite3 database;
            void close_socket();
            UdpServer *voiceServer;
            std::mutex *mtx;
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
            std::mutex mtx;
    };

#endif // CHAT_MESSAGE_HPP
