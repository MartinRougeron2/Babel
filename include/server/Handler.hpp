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

    namespace Handler
    {
        typedef std::string (*function_type)(int);

        std::string connect(int);
        std::string disconnect(int);
        std::string join(int);
        std::string leave(int);
        std::string call(int);

        std::map<std::string, function_type> mapped = {
            { "/connect", &connect },
            { "/disconnect", &disconnect },
            { "/join", &join },
            { "/leave", &leave },
            { "/call", &call }
        };
    };

#endif /* HANDLER_HPP */
