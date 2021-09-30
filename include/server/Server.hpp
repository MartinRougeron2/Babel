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

    namespace Handler
    {
        typedef std::string (*function_type_0)(int);
    
        std::string connect(int);
        std::string disconnect(int);
        std::string join(int);
        std::string leave(int);
        std::string call(int);


        std::map<std::string, function_type_0> mapped = {
            { "/connect", &connect },
            { "/disconnect", &disconnect },
            { "/join", &join },
            { "/leave", &leave },
            { "/call", &call }
        };
    };

#endif /* SERVER_HPP */
