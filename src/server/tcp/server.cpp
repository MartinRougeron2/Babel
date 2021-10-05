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
    this->database = Asqlite3();

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
    std::string user;
    std::string port;

    if (!err) {
        user = socket.remote_endpoint().address().to_string();
        port = socket.remote_endpoint().port();
        Session::add_user(user, port);

        new_data = new_data.substr(0, new_data.find('\n'));

        if (this->mapped.find(new_data) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << new_data << colors::reset << std::endl;
            (this->*this->mapped.at(new_data))(0);
        } else {
            std::cout << colors::yellow << FAIL << "command not found: " << new_data << colors::reset << std::endl;
        }
        socket.async_read_some(
            boost::asio::buffer(data, max_length),
            boost::bind(
                &Session::handle_read, this,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred)
            );
    } else if (err == boost::asio::error::eof) {
        std::cerr << colors::magenta << DONE << "A client left" << colors::reset << std::endl;
    } else {
        std::cerr << colors::red << FAIL << "err (recv): " << err.message() << colors::reset << std::endl;
    }
}

void Session::add_user(std::string user, std::string port)
{
    std::string full(user + ":" + port);

    if (std::find(this->users.begin(), this->users.end(), full) == this->users.end()) {
        std::cout << "adding: " << full << " to users" << std::endl;
        this->users.push_back(full);
    } else {
        std::cout << "user: " << full << " already registered" << std::endl;
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
        std::cerr << colors::red << FAIL << "err: " << err.message() << colors::reset << std::endl;
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
    std::cout << colors::green << DONE << "joinned: " << id << colors::reset << std::endl;

    return (false);
}

bool Session::leave(int id)
{
    std::cout << colors::green << DONE << "left: " << id << colors::reset << std::endl;

    return (false);
}

bool Session::call(int id)
{
    std::cout << colors::green << DONE << "called: " << id << colors::reset << std::endl;

    return (false);
}

bool Session::ping(int id)
{
    std::cout << colors::green << DONE << "pong: " << id << colors::reset << std::endl;

    return (false);
}
