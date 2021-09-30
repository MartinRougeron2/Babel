/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <iostream>
    #include <map>

    class server
    {
        public:
            server();
            ~server();

            std::string connect(int);
            std::string disconnect(int);
            std::string join(int);
            std::string leave(int);
            std::string call(int);

        private:
            typedef std::string (server::*function_type_0)(int);

            std::map<std::string, function_type_0> mapped = {
                { "/connect", &server::connect },
                { "/disconnect", &server::disconnect },
                { "/join", &server::join },
                { "/leave", &server::leave },
                { "/call", &server::call }
            };
    };

#endif /* SERVER_HPP */
