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
    #include <bitset>
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>
    #include <boost/array.hpp>

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
            typedef UserApp (TcpSession::*function_get)(std::string);

            std::map<std::string, function_type> mapped = {
                { "/login", &TcpSession::login },
                { "/logout", &TcpSession::logout },
                { "/join", &TcpSession::join },
                { "/hangup", &TcpSession::hangup },
                { "/accept", &TcpSession::accept },
                { "/refuse", &TcpSession::refuse },
                { "/add", &TcpSession::add },
                { "/remove", &TcpSession::remove },
                { "/call", &TcpSession::call },
                { "/ping", &TcpSession::ping },
                { "/check", &TcpSession::check_user },
                { "/linked", &TcpSession::check_linked },
                { "/exit", &TcpSession::close_server },
<<<<<<< HEAD
                { "/guic", &TcpSession::get_users_in_call },
                { "/getcontacts", &TcpSession::get_contacts }
            };

            std::map<std::string, int> encoder = {
                { "/login", 0b00000001 },
                { "/logout", 0b00000010 },
                { "/join", 0b00000011 },
                { "/hangup", 0b00000100 },
                { "/accept", 0b00000101 },
                { "/refuse", 0b00000111 },
                { "/add", 0b00001000 },
                { "/remove", 0b00001001 },
                { "/call", 0b00001011 },
                { "/ping", 0b00001111 },
                { "/check", 0b00010000 },
                { "/linked", 0b00010011 },
                { "/exit", 0b00010111 },
                { "/guic", 0b00011111 }
            };

            // DONE get_users_in_call
            // userapp get_user(user_name)
=======
                { "/getcontacts", &TcpSession::get_contacts },
                { "/getusersincall", &TcpSession::get_users_in_call }
            };

            std::map<std::string, function_get> getter = {
                { "/getuser", &TcpSession::get_user }
            };

            // DONE get_users_in_call
            // DONE userapp get_user(user_name)
>>>>>>> rebase Protocol
            // accept
            // refuse
            // DONE add contact
            // DONE remove contact
            // DONE check if users are linked
            // DONE check if user exists

            // MAPPED
            bool login(std::string, struct UserApp);
            bool logout(std::string, struct UserApp);
            bool join(std::string, struct UserApp);
            bool hangup(std::string, struct UserApp);
            bool call(std::string, struct UserApp);
            bool ping(std::string, struct UserApp);
            bool close_server(std::string, struct UserApp);
            bool check_user(std::string, struct UserApp);
            bool check_linked(std::string, struct UserApp);
            bool get_contacts(std::string, struct UserApp);
            bool get_users_in_call(std::string, struct UserApp);
            bool accept(std::string, struct UserApp);
            bool refuse(std::string, struct UserApp);
            bool add(std::string, struct UserApp);
            bool remove(std::string, struct UserApp);
            bool get_contacts(std::string, struct UserApp);

            bool get_users_in_call(std::string, struct UserApp);

            UserApp get_username_by_id(int);
            UserApp get_user(std::string);

            // GETTER
            UserApp get_user(std::string);

            void display(UserApp);

            S_Protocol decode(std::string);
            bool send(const char *);

            std::vector<UserApp> usersincall;

        private:
            tcp::socket socket;

            Protocol *recv;
            boost::array<std::bitset<6>, max_length> buffer;

            UserApp recvUser;
            Commands recvCommands;
            std::map<int, UserApp> users;
            Asqlite3 database;
            void close_socket();
            UdpServer *voiceServer;
            std::mutex *mtx;
            std::vector<UserApp> usersincall;
            std::map<std::string, UserApp> users_index;
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
