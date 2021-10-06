/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Protocol.hpp
*/

#ifndef PROTOCOL_HPP
    #define PROTOCOL_HPP

    #include <iostream>
    #include <common/User.h>

    struct Commands
    {
        std::string command;
        std::string arguments;
    };

    struct Protocol
    {
        Commands command;
        User user;
    };

#endif /* PROTOCOL_HPP */
