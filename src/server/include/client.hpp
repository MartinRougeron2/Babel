/*
** EPITECH PROJECT, 2019
** client.hpp
** File description:
** client
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include <vector>
    #include <string>
    #include <array>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>

    class entity {
        public:
            entity(void *_serv, boost::asio::ip::tcp::socket *sock);
            ~entity();

            std::string pseudo;
            std::string address;
            int port;
            boost::asio::ip::tcp::socket *sock;
            std::array<char, 512> buffer;
            void *serv;
            void procData(std::string data);
            void sendToClient(int id, std::vector<std::string> args);
            void handleData(std::string);
            void asyncReceive(void);
            void stop();
    };

#endif /* !ENTITY_HPP_ */

