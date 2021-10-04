/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.hpp
*/

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


#ifndef ASIO_HPP_
    #define ASIO_HPP_

    #define UDP_PORT 2001

    class UdpServer {
        public:
            UdpServer(boost::asio::io_service &io_service);

        private:
            void handleReceive(const boost::system::error_code &error,
                                std::size_t size);

            void handleSend(boost::shared_ptr <std::string> msg,
                             const boost::system::error_code &error,
                             std::size_t bytes_transferred);

            void get();
            udp::socket socket_;
            udp::endpoint remote_endpoint_;
            boost::array<char, 1> recv_buffer_;
    };

#endif /* !ASIO_HPP_ */
