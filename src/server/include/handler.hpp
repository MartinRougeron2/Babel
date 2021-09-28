/*
** EPITECH PROJECT, 2019
** handler.hpp
** File description:
** handler
*/

#ifndef HANDLER_HPP_
    #define HANDLER_HPP_

    #include <string>
    #include <vector>

    #include "entry.hpp"

    void dispatchPacket(int id, std::vector<std::string> args, entry *ent);
    void packet_handler(std::string data, entry *ent);
    int handler_id_manager(std::string data);

#endif /* !HANDLER_HPP_ */
