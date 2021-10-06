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
    int newId = this->addUser(
        new User("martinew", "127.0.0.1:45455", "")
    );
    this->addUser(new User("antho", "10.109.250.61:45456", ""), newId);
    for (auto userEnd : allGroups[0]->listUser)
        std::cout << userEnd.first->username << std::endl;
    this->get();
}

void UdpServer::sendStringToEndpoint(const std::string dataToSend, const
udp::endpoint remote_endpoint)
{
    boost::shared_ptr <std::string> message(new std::string(dataToSend));

    this->socket_.async_send_to(
        boost::asio::buffer(*message),
        remote_endpoint,
        boost::bind(
            &UdpServer::handleSend,
            this,
            message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void UdpServer::handleReceive(const boost::system::error_code &error,
                              std::size_t)
{
    User *sendUser = nullptr;
    std::vector<udp::endpoint *> others;

    if (!error || error == boost::asio::error::message_size) {
        std::string message = std::string(recv_buffer_.c_array());

        for (auto group : this->allGroups)
            for (auto userEndpoint : group->listUser)
                if (remote_endpoint_ == *userEndpoint.second)
                    sendUser = userEndpoint.first;

        std::cout << sendUser->username << std::endl;

        others = getOthersUsersEndpoint(sendUser);
        for (auto other : others)
            std::cout << (*other).port() << std::endl;
        for (auto const endpoint : others)
            this->sendStringToEndpoint(message, *endpoint);
        recv_buffer_.assign(0);
        this->get();
    }
}

void UdpServer::handleSend(boost::shared_ptr <std::string> msg,
                            const boost::system::error_code &error,
                            std::size_t bytes_transferred) {

}

void UdpServer::get() {
    this->socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        this->remote_endpoint_,
        boost::bind(
            &UdpServer::handleReceive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );

}


std::vector<udp::endpoint *> UdpServer::getOthersUsersEndpoint(const User *userFrom)
{
    Group userGroup({}, 0);
    std::vector<udp::endpoint *> others;

    if (userFrom == nullptr)
        return {};

    for (auto group : this->allGroups)
        for (auto user : group->listUser)
            if (user.first->username == userFrom->username)
                userGroup.listUser = group->listUser;

    for (auto user : userGroup.listUser)
        if (user.first->username != userFrom->username)
            others.push_back(user.second);

    return others;
}

int UdpServer::addUser(User * userToAdd)
{
    int newId = this->id++;
    this->allGroups.push_back(
        new Group({userToAdd}, newId)
    );
    return newId;
}


void UdpServer::addUser(User * userToAdd, int groupId)
{
    for (auto group : this->allGroups) {
        if (group->id == groupId)
            group->addUser(userToAdd);
    }
}

int UdpServer::addUser(std::vector<User *> usersToAdd)
{
    int newId = this->id++;
    this->allGroups.push_back(
        new Group(usersToAdd, newId)
    );
    return newId;
}

void UdpServer::addUser(User * userToAdd, User * userToFind)
{
    for (auto group : this->allGroups)
        for (auto user : group->listUser)
            if (user.first->username == userToFind->username)
                group->addUser(userToAdd);
}

void UdpServer::addUser(std::vector <User *> usersToAdd, int groupId)
{
    for (auto group : this->allGroups) {
        if (group->id == groupId)
            for (auto user : usersToAdd)
                group->addUser(user);
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
        boost::asio::ip::address::from_string(address),std::stoi(port)
    );
}
