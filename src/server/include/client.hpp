/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** client.hpp
*/

#ifndef entry_HPP_
    #define entry_HPP_

    #include <vector>
    #include <string>
    #include <array>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>

    class entry {
        public:
            entry(void *_serv, boost::asio::ip::tcp::socket *sock);
            ~entry();

            std::string pseudo;
            std::string address;
            int port;
            boost::asio::ip::tcp::socket *sock;
            std::array<char, 512> buffer;
            void *serv;
            void resume(std::string data);
            void sendToClient(int id, std::vector<std::string> args);
            void handleData(std::string);
            void asyncReceive(void);
            void stop();
    };

#endif /* !entry_HPP_ */

