/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Udp
*/

#include "client/protocol/ClientUdp.hpp"

using boost::asio::ip::udp;

ClientUdp::ClientUdp(const std::string ip, boost::asio::io_service ioService): sock(ioService)
{
    udp::resolver resolver(ioService);

//     // type ip (IP V4) | IP | hostname
     udp::resolver::query query(udp::v4(), ip);
//     //  udp::resolver::query query(udp::v4(), ip.c_str(), "daytime");

    this->receiverEndpoint = *resolver.resolve(query);
    udp::socket socket(ioService);
    sock.open(udp::v4());
}

ClientUdp::~ClientUdp()
{
}

void ClientUdp::sendMessage(const std::string &msg)
{
    sock.send_to(boost::asio::buffer(msg), this->receiverEndpoint);
}

std::string ClientUdp::getMessage()
{
    udp::endpoint senderEndpoint;
    std::string recv;

    // TODO Init recv to sample size with codec
    sock.receive_from(boost::asio::buffer(recv), senderEndpoint);
    return recv;
}

/*
    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), SERVER_IP, MESSAGE ???);
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io_service);0
    socket.open(udp::v4());

    boost::array<char, 1> send_buf  = { 0 };
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
 */
