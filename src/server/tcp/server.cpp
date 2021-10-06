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
}

void Session::start()
{
    socket.async_read_some(
        boost::asio::buffer(this->recv, max_length),
        boost::bind(
            &Session::handle_read, this,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
        );
}

void Session::handle_read(std::shared_ptr<Session> &s, const boost::system::error_code &err, std::size_t bytes_transferred)
{
    User decoded;
 
    if (!err) {
        if (this->mapped.find(this->recv->command.command) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << this->recv->command.command << colors::reset << std::endl;
            (this->*this->mapped.at(this->recv->command.command))(this->recv->command.arguments, this->recv->user);
        } else {
            std::cout << colors::yellow << FAIL << "command not found: " << this->recv->command.command << colors::reset << std::endl;
        }
        socket.async_read_some(
            boost::asio::buffer(this->recv, max_length),
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

User Session::decoder(std::string recv, User user)
{
    std::string delimiter = ";";

    // GET USERNAME
    user.username = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());

    // GET PASSWORD
    user.password = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());

    // GET ADDRESS
    user.address = user.address;
    /*
    ids.address = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());
    */

    // GET COMMAND
    this->current_command = recv.substr(0, recv.find(delimiter));
    this->current_arguments = recv.erase(0, recv.find(delimiter) + delimiter.length());

    Session::display(user);

    return (user);
}

void Session::display(User user)
{
    std::cout << "-----------" << std::endl;
    std::cout << "Username:  " << user.username << std::endl;
    std::cout << "Password:  " << user.password << std::endl;
    std::cout << "Address:   " << user.address << std::endl;
    std::cout << "Command:   " << this->current_command << std::endl;
    std::cout << "Arguments: " << this->current_arguments << std::endl;
    std::cout << "-----------" << std::endl;
}

User Session::set_new_user(void)
{
    User new_user;
    std::string user(socket.remote_endpoint().address().to_string());
    std::string port(std::to_string(socket.remote_endpoint().port()));
    std::string full(user + ":" + port);

    new_user.username = EMPTY;
    new_user.password = EMPTY;
    new_user.address = full;

    return (new_user);
}

bool Session::login(std::string arguments, struct User user)
{
    Session::display(user);

    if (this->database.uploadData(user) == true) {
        std::cout << colors::green << DONE << "user created: " << user.username << colors::reset << std::endl;
    } else {
        std::cout << colors::yellow << FAIL << "user already present: " << user.username << colors::reset << std::endl;
    }
    if (this->database.login(user) == this->database.SUCCESS) {
        std::cout << colors::green << DONE << "user: " << user.username << " has been logged" << colors::reset << std::endl;
        return (true);
    }
    std::cout << colors::yellow << FAIL << "user: " << user.username << " failed to login" << colors::reset << std::endl;

    return (false);
}

bool Session::logout(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "logged out: " << user.username << colors::reset << std::endl;

    return (false);
}

bool Session::join(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "joinned: " << user.username << colors::reset << std::endl;

    return (false);
}

bool Session::leave(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "left: " << user.username << colors::reset << std::endl;

    return (false);
}

bool Session::call(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "called: " << user.username << colors::reset << std::endl;

    return (false);
}

bool Session::ping(std::string arguments, struct User user)
{
    Session::display(user);

    std::cout << colors::green << DONE << "pong: " << user.username << colors::reset << std::endl;

    return (false);
}

bool Session::exit(std::string arguments, struct User user)
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
