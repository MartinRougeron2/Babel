/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.hpp
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "../common/User.h"
#include "../common/standard.h"

using boost::asio::ip::udp;


#ifndef ASIO_HPP_
    #define ASIO_HPP_

    #define UDP_PORT 2001

        class Group {
            public:
                Group(std::vector<User *> newUsers, int newId);
                ~Group();
                std::map<User * , boost::asio::ip::udp::endpoint *> listUser;
                int id;
                void addUser(User * newUser);
        };



    class UdpServer {
        public:
            UdpServer(boost::asio::io_service &io_service);
            int  addUser(User * userToAdd);
            void addUser(User * userToAdd, int groupId);
            int  addUser(std::vector<User *> usersToAdd);
            void addUser(std::vector<User *> usersToAdd, int groupId);
            void addUser(User * userToAdd, User * userToFind);

        private:
            void handleReceive(const boost::system::error_code &error,
                                std::size_t size);

            void handleSend(boost::shared_ptr <std::string> msg,
                             const boost::system::error_code &error,
                             std::size_t bytes_transferred);


            std::vector<udp::endpoint *> getOthersUsersEndpoint(const User *userFrom);
            void get();
            void sendStringToEndpoint(const std::string dataToSend,
                                      const udp::endpoint remote_endpoint);


            udp::socket socket_;
            udp::endpoint remote_endpoint_;
            boost::array<char, 100> recv_buffer_;
            std::vector<Group *> allGroups;
            int id = 0;
    };

#endif /* !ASIO_HPP_ */
