/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Handler.hpp
*/

#ifndef HANDLER_HPP
    #define HANDLER_HPP

    #include <iostream>
    #include <map>

    class Handler
    {
        public:
            Handler();
            ~Handler();

            typedef std::string (Handler::*function_type)(int);

            std::map<std::string, function_type> mapped = {
                { "/connect", &Handler::connect },
                { "/disconnect", &Handler::disconnect },
                { "/join", &Handler::join },
                { "/leave", &Handler::leave },
                { "/call", &Handler::call },
                { "ping", &Handler::ping }
            };

            std::string connect(int);
            std::string disconnect(int);
            std::string join(int);
            std::string leave(int);
            std::string call(int);
            std::string ping(int);
    };

#endif /* HANDLER_HPP */
