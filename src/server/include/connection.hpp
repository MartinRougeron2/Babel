/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** connection.hpp
*/

#ifndef CONNECTION_HPP_
    #define CONNECTION_HPP_

    #include <vector>
    #include <string>

    #include "entry.hpp"
    #include "server.hpp"

    void connection_welcome(std::vector<std::string> args, entry *ent);
    void connection_connect(std::vector<std::string> args, entry *ent);
    void connection_pending(std::vector<std::string> args, entry *ent);
    void connection_pending_accept(std::vector<std::string> args, entry *ent);
    void connection_pending_refuse(std::vector<std::string> args, entry *ent);

#endif /* CONNECTION_HPP_ */
