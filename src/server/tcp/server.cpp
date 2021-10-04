/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "server/TCP.hpp"

#include "Colors.hpp"

Session::Session(boost::asio::io_service &ios) : socket(ios)
{
    return;
}

tcp::socket &Session::get_socket()
{
    return socket;
}

void Session::start()
{
    socket.async_read_some(
        boost::asio::buffer(data, max_length),
        boost::bind(
            &Session::handle_read, this,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
        );
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, std::size_t bytes_transferred)
{
    std::string new_data(data);

    if (!err) {
        new_data = new_data.substr(0, new_data.find('\n'));

        if (this->mapped.find(new_data) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << new_data << colors::reset << std::endl;
            (this->*this->mapped.at(new_data))(0);
        } else {
            std::cout << colors::red << FAIL << "command not found: " << new_data << colors::reset << std::endl;
        }
        socket.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(
                &Session::handle_read, this,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred)
            );
    } else {
        std::cerr << colors::bold << FAIL << "err (recv): " << err.message() << colors::reset << std::endl;
    }
}

Server::Server(boost::asio::io_service &ios, short port) : ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port))
{
    std::shared_ptr<Session> session = std::make_shared<Session>(ios);
    acceptor.async_accept(
        session->get_socket(),
        boost::bind(
            &Server::handle_accept,
            this,
            session,
            boost::asio::placeholders::error
        )
    );
}

void Server::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err)
{
    if (!err) {
        session->start();
        session = std::make_shared<Session>(ios);
        acceptor.async_accept(
            session->get_socket(),
            boost::bind(
                &Server::handle_accept,
                this,
                session,
                boost::asio::placeholders::error
            )
        );
    } else {
        std::cerr << colors::bold << FAIL << "err: " << err.message() << colors::reset << std::endl;
        session.reset();
    }
}

bool Session::login(int id)
{
    std::cout << colors::green << DONE << "logged: " << id << colors::reset << std::endl;

    return (false);
}

bool Session::logout(int id)
{
    std::cout << colors::green << DONE << "logout: " << id << colors::reset << std::endl;

    return (false);
}

bool Session::join(int id)
{
    std::cout << "joinned: " << id << std::endl;

    return (false);
}

bool Session::leave(int id)
{
    std::cout << "left: " << id << std::endl;

    return (false);
}

bool Session::call(int id)
{
    std::cout << "called: " << id << std::endl;

    return (false);
}

bool Session::ping(int id)
{
    std::cout << "pong" << id << std::endl;

    return (false);
}
