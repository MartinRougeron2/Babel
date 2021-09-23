/*
** EPITECH PROJECT, 2019
** connectionHandler.hpp
** File description:
** connectionHandler
*/

#ifndef CONNECTIONHANDLER_HPP_
    #define CONNECTIONHANDLER_HPP_

    // # Lib Imports

    #include <vector>
    #include <string>

    // # Local Imports

    #include "entity.hpp"
    #include "server.hpp"

    void HandleWelcome(std::vector<std::string> args, entity *ent);
    void HandleConnect(std::vector<std::string> args, entity *ent);
    void HandlePendingRequest(std::vector<std::string> args, entity *ent);
    void HandleAcceptPending(std::vector<std::string> args, entity *ent);
    void HandleRefusePending(std::vector<std::string> args, entity *ent);

#endif /* !CONNECTIONHANDLER_HPP_ */
