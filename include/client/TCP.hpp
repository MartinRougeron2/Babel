/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#ifndef TCP_HPP
    #define TCP_HPP

    #include <iostream>
    #include <string>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/uio.h>
    #include <sys/time.h>
    #include <sys/wait.h>
    #include <fcntl.h>
    #include <fstream>

    #include "Protocol.hpp"

    #define TCP_IP "127.0.0.1"
    #define TCP_PORT 2000

    class TCP
    {
        public:
            TCP();
            ~TCP();

            bool build_init();
            bool build_connect();
            bool build();
            bool run();

        private:
            // client settings
            char *server_ip;
            int server_port;

            char msg[1500];

            struct hostent *host;
            sockaddr_in address;

            int client_socket;
            int client_status;

            // status
            bool running;
    };

#endif /* TCP_HPP */