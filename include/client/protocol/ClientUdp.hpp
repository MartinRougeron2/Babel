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
#include <boost/bind.hpp>
#include <array>
#define UPD_PORT 2001

class ClientUdp {
    public:
        ClientUdp(const std::string ip, boost::asio::io_service &ioService);
        ~ClientUdp();

        void sendMessage(const std::string &msg);
        void sendMessage(const std::vector<unsigned char> &msg);

        std::vector<unsigned short> getMessage();
        void read(const boost::system::error_code &error, size_t bytes_recvd);

protected:
    private:
        boost::asio::ip::udp::endpoint receiverEndpoint;
        boost::asio::ip::udp::socket *sock;
};

#endif /* !UDP_HPP_ */
