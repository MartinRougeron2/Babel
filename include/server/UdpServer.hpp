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
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>



#include "../common/User.h"
#include "../common/standard.h"

using boost::asio::ip::udp;


#ifndef ASIO_HPP_
    #define ASIO_HPP_

    #define UDP_PORT 2001

class UdpServer;
struct UdpSession;

struct UdpSession : boost::enable_shared_from_this<UdpSession> {

    UdpSession(UdpServer *server);

    void handle_sent(const boost::system::error_code &ec, std::size_t);

    udp::endpoint remote_endpoint_;
    boost::array<char, 100> recv_buffer_;
    std::string message;
    UdpServer *server_;

    bool operator==(const UdpSession &other)
    {
        return this->remote_endpoint_ == other.remote_endpoint_;
    }
};

typedef boost::shared_ptr<UdpSession> shared_session;


class Group {
    public:
        Group();
        Group(shared_session session);
        Group(std::vector<shared_session> sessions);
        ~Group();

        int  addSession(const std::string address,
                        std::vector<shared_session> allSessions);
        void addSession(const shared_session &session);
        void addSession(const std::vector<shared_session> sessions);
        std::vector<shared_session> sessions;
};

class UdpServer {
    public:
        UdpServer(boost::asio::io_service &io_service);

        int  createGroup(shared_session session);
        int  addToGroup(int groupId, shared_session sessionToAdd);
        bool removeFromGroup(int groupId, shared_session sessionToRemove);
        int join(std::string addressPort);
        int join(std::string addressPort, int id);

    private:

        void receive_session();
        std::vector<shared_session> get_related(const shared_session session) const;

        void handle_receive(const shared_session session, const boost::system::error_code &ec, std::size_t);

        int id = 0;
        udp::socket socket_;
        boost::asio::io_service::strand strand_;
        std::map<int, Group> groups;
        std::vector<shared_session> allSessions;

        friend struct UdpSession;
};


#endif /* !ASIO_HPP_ */
