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
    for (size_t i = 0; i < others.size(); i++)
        if (others[i] == session)
            others.erase(others.begin() + i);
    return others;
}

void UdpServer::handle_receive(const shared_session session, const boost::system::error_code &ec,
                    std::size_t)
{
    std::vector<shared_session> others_sessions = get_related(session);

    std::cout << session->recv_buffer_.c_array();

    for (auto others_session : others_sessions)
        post(socket_.get_executor(), bind(&UdpSession::handle_request,
                                          others_session, ec));

    receive_session();
}

void UdpServer::enqueue_response(shared_session const &session)
{
    socket_.async_send_to(
        boost::asio::buffer(session->message),
        session->remote_endpoint_,
        strand_.wrap(
            bind(
                &UdpSession::handle_sent,
                session, // keep-alive of buffer/endpoint
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        )
    );
}
