/*
** EPITECH PROJECT, 2019
** server.hpp
** File description:
** server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include <vector>

    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include "entry.hpp"
    #include "network.hpp"
    #include "handler.hpp"

    class server {
        public:
            std::vector<entry*> clients;
            network *net;
            bool running;

            server(int _port);
            ~server();
            entry *get_address(std::string);
            entry *get_pseudo(std::string);
            bool check_username(std::string);
            void accept_connection();
            void handler();
            void remove_username(std::string);
            void stop();
    };



#endif /* !SERVER_HPP_ */

