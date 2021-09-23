/*
** EPITECH PROJECT, 2019
** network.cpp
** File description:
** network
*/

#include <boost/bind.hpp>

#include "network.hpp"
#include "server.hpp"

// # Builder / Destructor

network::network(void *_serv, int _port) : sig(service, SIGTERM, SIGINT), acceptor(NULL), listener(NULL), port(-1)
{
    serv = _serv;
    port = _port;
    running = false;
}

network::~network()
{
    running = false;
    stop();
}

// # Methods

void network::stop()
{
    running = false;
    service.stop();
}

void network::start()
{
    acceptor = boost::shared_ptr<boost::asio::ip::tcp::acceptor>(new boost::asio::ip::tcp::acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)));
    std::cout << "Listening on port " << port << std::endl;
    std::cout << "Waiting for connection ..." << std::endl;
    running = true;
    accept();
    service.run(errorcode);
}

void network::accept()
{
    if (!running)
        return;
    boost::asio::ip::tcp::socket *socket = new boost::asio::ip::tcp::socket(service);
    sockets.push_back(socket);
    acceptor->async_accept(*socket, [this](const boost::system::error_code &error) {
        if (!running)
            return;
        if (error)
            std::cout << "Can't accept connection, error occured" << std::endl;
        else {
            server *obj = (server *)serv;
            obj->handleClient();
        }
        accept();
    });
}

void network::setSocketEvent(INetwork::SocketEvent *_listener)
{
    listener = _listener;
}
