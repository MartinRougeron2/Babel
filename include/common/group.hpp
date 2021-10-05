/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** Group
*/

#include "standard.h"
#include "User.h"

#ifndef BABEL_GROUP_HPP
    #define BABEL_GROUP_HPP

    class Group {
        public:
            Group(std::vector<User> newUsers, int newId);
            ~Group();
            std::vector<User> listUser;
            int id;
    };

#endif //BABEL_GROUP_HPP
