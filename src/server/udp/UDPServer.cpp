/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.cpp
*/

#include "server/UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &io_service) :
    socket_(io_service, udp::endpoint(udp::v4(), UDP_PORT)) {

    this->get();
}

void UdpServer::handleReceive(const boost::system::error_code &error, std::size_t) {
    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr <std::string> message(new std::string("PTDR t ki ?"));

        socket_.async_send_to(
            boost::asio::buffer(*message),
            remote_endpoint_,
            boost::bind(
                &UdpServer::handleSend,
                this,
                message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );

        get();
    }
}

void UdpServer::handleSend(boost::shared_ptr <std::string> msg,
                            const boost::system::error_code &error,
                            std::size_t bytes_transferred) {

}

void UdpServer::get() {
    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        remote_endpoint_,
        boost::bind(
            &UdpServer::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}