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

    void HandleWelcome(std::vector<std::string> args, entry *ent);
    void HandleConnect(std::vector<std::string> args, entry *ent);
    void HandlePendingRequest(std::vector<std::string> args, entry *ent);
    void HandleAcceptPending(std::vector<std::string> args, entry *ent);
    void HandleRefusePending(std::vector<std::string> args, entry *ent);

#endif /* CONNECTION_HPP_ */
