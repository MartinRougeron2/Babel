/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include "portaudio.h"
#include "client/Asqlite3.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    Asqlite3 db;

    db.uploadData({"ze", "deodeo", "127.0.0.1"});
    /*if (db.login({"a", "aa"}) == Asqlite3::SUCCESS) {
        std::cout << "yeah\n";
    }*/
    db.linkUser("zz", "ze");
    db.getLinkedUser("zz");
    std::cout << db.getUser("");
}