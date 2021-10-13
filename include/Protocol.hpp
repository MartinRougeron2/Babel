/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Protocol.hpp
*/

#ifndef PROTOCOL_HPP
    #define PROTOCOL_HPP

    #include <iostream>
    #include <string>

    #include "common/User.hpp"

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

#endif /* PROTOCOL_HPP */
