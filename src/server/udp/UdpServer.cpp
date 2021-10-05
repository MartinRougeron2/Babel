/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** UDP.cpp
*/

#include "server/UdpServer.hpp"
#include "../../../include/server/UdpServer.hpp"

UdpServer::UdpServer(boost::asio::io_service &io_service) :
    socket_(io_service, udp::endpoint(udp::v4(), UDP_PORT)) {

    this->get();
}

void UdpServer::handleReceive(const boost::system::error_code &error,
                              std::size_t) {
    if (!error || error == boost::asio::error::message_size) {
        boost::shared_ptr <std::string> message(new std::string("PTDR t ki ?"));

        std::cout << remote_endpoint_.address().to_string() << ":";
        std::cout << remote_endpoint_.port() << std::endl;

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

Group::Group(std::vector<User *> newUsers, int newId)
{
    this->id = newId;

    for (auto user : newUsers) {
        this->addUser(user);
    }
}

Group::~Group()
{
}

void Group::addUser(User * user)
{
    size_t separationPos = user->address.find(':');
    std::string address = user->address.substr(0, separationPos);
    std::string port = user->address.substr(separationPos + 1);

    this->listUser[user] = new boost::asio::ip::udp::endpoint(
        boost::asio::ip::address::from_string(user->address),std::stoi(port)
    );
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

std::vector<User *> UdpServer::getOthersUsers(User * userFrom)
{
    Group userGroup({}, 0);
    std::vector<User *> others;


    for (auto group : allGroups)
        for (auto user : group->listUser)
            if (user.first->username == userFrom->username)
                userGroup.listUser = group->listUser;
    for (auto user : userGroup.listUser)
        if (user.first->username != userFrom->username)
            others.push_back(user.first);
    return others;
}

int UdpServer::addUser(User * userToAdd)
{
    int newId = id++;
    this->allGroups.push_back(
        new Group({userToAdd}, newId)
    );
    return newId;
}


void UdpServer::addUser(User * userToAdd, int groupId)
{
    for (auto group : allGroups) {
        if (group->id == groupId)
            group->addUser(userToAdd);
    }
}

int UdpServer::addUser(std::vector<User *> usersToAdd)
{
    int newId = id++;
    this->allGroups.push_back(
        new Group(usersToAdd, newId)
    );
    return newId;
}

void UdpServer::addUser(User * userToAdd, User * userToFind)
{
    for (auto group : allGroups)
        for (auto user : group->listUser)
            if (user.first->username == userToFind->username)
                group->addUser(userToAdd);
}

void UdpServer::addUser(std::vector <User *> usersToAdd, int groupId)
{
    for (auto group : allGroups) {
        if (group->id == groupId)
            for (auto user : usersToAdd)
                group->addUser(user);
    }
}
