/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.cpp
*/

#include "server/UdpServer.hpp"
#include "../../../include/server/UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &io_service) : socket_(io_service,
                                                              udp::endpoint(udp::v4(), UDP_PORT)), strand_(io_service)
{
    receive_session();
}

int UdpServer::createGroup(shared_session session)
{
    groups[id++] = Group(session);
    return id;
}

int UdpServer::addToGroup(int groupId, shared_session sessionToAdd)
{
    groups[groupId].addSession(sessionToAdd);
    return groupId;
}

bool UdpServer::removeFromGroup(int groupId, shared_session sessionToRemove)
{
    bool isRemoved = false;

    for (size_t i = 0; i < groups[groupId].sessions.size(); i++)
        if (sessionToRemove == groups[groupId].sessions[i]) {
            isRemoved = true;
            groups[groupId].sessions.erase(
                groups[groupId].sessions.begin() + i
            );
        }
    return isRemoved;
}

void UdpServer::receive_session()
{
    auto session = boost::make_shared<UdpSession>(this);

    this->allSessions.push_back(session);

    this->socket_.async_receive_from(
        boost::asio::buffer(session->recv_buffer_),
        session->remote_endpoint_,
        strand_.wrap(
            bind(&UdpServer::handle_receive,
                 this,
                 session,
                 boost::asio::placeholders::error,
                 boost::asio::placeholders::bytes_transferred)));
}

int UdpServer::join(std::string addressPort)
{
    this->groups[this->id++].addSession(addressPort, this->allSessions);
    return this->id;
}

int UdpServer::join(std::string addressPort, int _id)
{
    this->groups[_id].addSession(addressPort, this->allSessions);
    return _id;
}

std::vector<shared_session> UdpServer::get_related(const shared_session session)
const
{
    std::vector<shared_session> others = {};
    // ? get user group
    for (const std::pair<const int, Group> &group : this->groups)
        for (auto member : group.second.sessions)
            if (member == session) {
                others = group.second.sessions;
                break;
            }
    // pop sender out
    /// TO TEST
//    for (size_t i = 0; i < others.size(); i++)
//        if (others[i] == session)
//            others.erase(others.begin() + i);
//    for (auto other: others)
//        std::cout << other->remote_endpoint_.address().to_string() << std::endl;
/// ----------------------------
    return others;
}

void UdpServer::handle_receive(const shared_session session, const boost::system::error_code &ec,
                    std::size_t)
{
    std::vector<shared_session> others_sessions = get_related(session);

    for (auto others_session : others_sessions) {
        socket_.async_send_to(
            boost::asio::buffer(session->recv_buffer_),
            others_session->remote_endpoint_,
            strand_.wrap(
                bind(
                    &UdpSession::handle_sent,
                    others_session,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
            )
        );
    }
    session->recv_buffer_.assign(0);

    receive_session();
}