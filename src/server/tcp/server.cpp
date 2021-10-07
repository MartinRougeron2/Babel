/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "server/TCP.hpp"

#include "Colors.hpp"

TCPServer::TCPServer(boost::asio::io_service &ios, short port) : ios(ios), acceptor(ios, tcp::endpoint(tcp::v4(), port))
{
    std::shared_ptr<Session> session = std::make_shared<Session>(ios);
    acceptor.async_accept(
        session->get_socket(),
        boost::bind(
            &TCPServer::handle_accept,
            this,
            session,
            boost::asio::placeholders::error
        )
    );
}

void TCPServer::handle_accept(std::shared_ptr<Session> session, const boost::system::error_code &err)
{
    if (!err) {
        session->start();
        session = std::make_shared<Session>(ios);
        acceptor.async_accept(
            session->get_socket(),
            boost::bind(
                &TCPServer::handle_accept,
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

Session::Session(boost::asio::io_service &ios) : socket(ios)
{
    this->database = Asqlite3();

    return;
}

tcp::socket &Session::get_socket()
{
    return socket;
}

void Session::close_socket()
{
    std::cout << colors::blue << WAIT << "closing socket..." << colors::reset << std::endl;
    try {
        Session::get_socket().close();
    } catch (std::exception &e) {
        std::cout << colors::red << FAIL << "error in closing socket " << e.what() << colors::reset << std::endl;
        return;
    }
    std::cout << colors::green << DONE << "socket closed" << colors::reset << std::endl;
    exit(0);
}

void Session::start()
{
    socket.async_read_some(
        boost::asio::buffer(this->recv, max_length),
        boost::bind(
            &Session::handle_read,
            this,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, std::size_t bytes_transferred)
{
    // FIX: Bad Address => due to this->recv memory allocation size

    if (!err) {
        this->recv_user = Session::C_user_to_user(this->recv->user);
        this->recv_commands = Session::C_command_to_commands(this->recv->command);

        if (this->mapped.find(this->recv_commands.command) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << this->recv_commands.command << colors::reset << std::endl;
            (this->*this->mapped.at(this->recv_commands.command))(this->recv_commands.arguments, this->recv_user);
        } else {
            std::cout << colors::yellow << FAIL << "command not found: " << this->recv_commands.command << colors::reset << std::endl;
        }
        socket.async_read_some(
            boost::asio::buffer(this->recv, max_length),
            boost::bind(
                &Session::handle_read,
                this,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
    } else if (err == boost::asio::error::eof) {
        std::cerr << colors::magenta << DONE << "A client left" << colors::reset << std::endl;
    } else {
        std::cerr << colors::red << FAIL << "err (recv): " << err.message() << colors::reset << std::endl;
        Session::close_socket();
    }
}

void Session::display(User user)
{
    std::cout << "-----------" << std::endl;
    std::cout << "Username:  " << user.username << std::endl;
    std::cout << "Password:  " << user.password << std::endl;
    std::cout << "LHost:     " << socket.local_endpoint() << std::endl;
    std::cout << "Socket:    " << socket.remote_endpoint() << std::endl;
    std::cout << "-----------" << std::endl;
}

User Session::C_user_to_user(C_User c_user)
{
    std::cout << "converting user..." << std::endl;
    User user;

    user.username = std::string(c_user.username);
    user.password = std::string(c_user.password);
    user.address = std::string(c_user.address);
    user.id = c_user.id;

    Session::display(user);

    std::cout << "converted user" << std::endl;

    return (user);
}

Commands Session::C_command_to_commands(C_Commands c_commands)
{
    std::cout << "converting commands..." << std::endl;
    Commands commands;

    commands.command = std::string(c_commands.command);
    commands.arguments = std::string(c_commands.arguments);

    std::cout << "converted commands" << std::endl;

    return (commands);
}

bool Session::login(std::string arguments, struct User user)
{
    Session::display(user);

    if (this->database.uploadData(user) == true) {
        std::cout << colors::green << DONE << "user created" << colors::reset << std::endl;
    } else {
        std::cout << colors::yellow << FAIL << "user already present" << colors::reset << std::endl;
    }
    if (this->database.login(user) == this->database.SUCCESS) {
        std::cout << colors::green << DONE << "logged" << colors::reset << std::endl;
        return (true);
    }
    std::cout << colors::yellow << FAIL << "failed to login" << colors::reset << std::endl;

    return (false);
}

bool Session::logout(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "logged out" << colors::reset << std::endl;

    return (false);
}

bool Session::join(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "joinned" << colors::reset << std::endl;

    return (false);
}

bool Session::leave(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "left" << colors::reset << std::endl;

    return (false);
}

bool Session::call(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "called" << colors::reset << std::endl;

    return (false);
}

bool Session::ping(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "pong" << colors::reset << std::endl;

    return (false);
}

bool Session::close_server(std::string arguments, struct User user)
{
    Session::display(user);

    if (user.username == "admin" && user.password == "admin") {
        std::cout << colors::green << DONE << "user authorized" << colors::reset << std::endl;
        Session::close_socket();
    } else {
        std::cout << colors::red << FAIL << "user not authorized" << colors::reset << std::endl;
    }

    return (false);
}
