/*
** EPITECH PROJECT, 2019
** network.hpp
** File description:
** network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_

    #include <iostream>
    #include <stdio.h>
    #include <string.h>
    #include <string>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <vector>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>

    class INetwork {
        public:
            class SocketEvent {
			    public:
				    virtual	~SocketEvent() {}
		    };
            virtual void setSocketEvent(INetwork::SocketEvent *listener) = 0;
    };

    class network : private INetwork {
        public:
            network(void *, int port);
            network();
            ~network();
            
            boost::asio::io_service service;
            boost::asio::signal_set sig;
            boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor;
            std::vector<boost::asio::ip::tcp::socket*> sockets;
            INetwork::SocketEvent* listener;
            boost::system::error_code errorcode;
            
            void *serv;
            int port;
            bool running;
            void start();
            void stop();
            void accept();
            void setSocketEvent(INetwork::SocketEvent *listener);
    };


#endif /* !NETWORK_HPP_ */
