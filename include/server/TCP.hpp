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

    #define TCP_PORT 2000

    class TCP
    {
        public:
            TCP();
            ~TCP();

            bool build();
            bool build_init();
            bool build_socket();
            bool build_bind();
            bool build_listen();
            bool build_accept();
            bool run();

        private:
            // server settings
            int port;
            int server_socket;
            int server_bind;
            int server_udp_socket;
            
            char msg[1500];
            fd_set rset;
            int max_sockets;
            
            sockaddr_in address;
            sockaddr_in socket_address;
            socklen_t socket_size;

            // server status
            bool running;
    };

#endif /* TCP_HPP */