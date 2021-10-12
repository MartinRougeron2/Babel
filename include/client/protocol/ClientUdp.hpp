/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Udp
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <string>
#include <boost/asio.hpp>
#include <array>

#define UPD_PORT 2001

class ClientUdp {
    public:
        ClientUdp(const std::string ip, boost::asio::io_service ioService);
        ~ClientUdp();

        void sendMessage(const std::string &msg);
        std::string getMessage();

    protected:
    private:
        boost::asio::ip::udp::endpoint receiverEndpoint;
        boost::asio::ip::udp::socket sock;
};

#endif /* !UDP_HPP_ */
