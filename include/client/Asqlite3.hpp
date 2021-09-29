/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ASqlite3
*/

#ifndef ASQLITE3_HPP_
#define ASQLITE3_HPP_

#include "sqlite3.h"
#include <string>
#include <vector>

struct User {
    std::string username;
    std::string password;
    std::string address;
};

class Asqlite3 {
    public:
        Asqlite3();
        ~Asqlite3();

        enum loginCode {SUCCESS, USER_NOT_EXIST, BAD_PASSWORD};
        bool uploadData(struct User user);
        loginCode login(struct User user);
        std::string getUser(std::string username);
        bool linkUser(std::string userfrom, std::string userto);
        std::string getIdByUsername(std::string username);
        std::vector<struct User> getLinkedUser(std::string username);

    protected:
    private:
        std::string _dir = "./userdb.db";
        std::string _res;
        std::vector<struct User> _linkedUser;

        static int callbackUserExist(void *, int argc, char** argv, char** azColName);
        static int callbackGetUser(void *, int argc, char** argv, char** azColName);
        static int callbackFillContact(void *, int argc, char** argv, char** azColName);
};

#endif /* !ASQLITE3_HPP_ */
