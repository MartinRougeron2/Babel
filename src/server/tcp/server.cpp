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
        //boost::asio::buffer(this->recv, max_length),
        boost::asio::buffer(this->buffer, max_length),
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
    // FIX: Bad Address
    S_Protocol response;

    if (!err) {
        /*
        this->recv_user = Session::C_user_to_user(this->recv->user);
        this->recv_commands = Session::C_command_to_commands(this->recv->command);

        if (this->mapped.find(this->recv_commands.command) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << this->recv_commands.command << colors::reset << std::endl;
            (this->*this->mapped.at(this->recv_commands.command))(this->recv_commands.arguments, this->recv_user);
        } else {
            std::cout << colors::yellow << FAIL << "command not found: " << this->recv_commands.command << colors::reset << std::endl;
        }
        */
        std::cout << this->buffer << std::endl;
        response = Session::decode(this->buffer);
        if (this->mapped.find(response.command.command) != this->mapped.end()) {
            (this->*this->mapped.at(response.command.command))(response.command.arguments, response.user);
        } else {
            Session::send(set_string("command not found\n"));
        }
        socket.async_read_some(
            //boost::asio::buffer(this->recv, max_length),
            boost::asio::buffer(this->buffer, max_length),
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

S_Protocol Session::decode(std::string recv)
{
    std::string delimiter = ";";
    std::string full(socket.local_endpoint().address().to_string() + ":" + std::to_string(socket.local_endpoint().port()));
    S_Protocol protocol;

    recv = recv.substr(0, recv.find('\n'));

    // GET USERNAME
    protocol.user.username = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());

    // GET PASSWORD
    protocol.user.password = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());

    protocol.user.address = full;
    /*
    ids.address = recv.substr(0, recv.find(delimiter));
    recv = recv.erase(0, recv.find(delimiter) + delimiter.length());
    */

    // GET COMMAND
    protocol.command.command = recv.substr(0, recv.find(delimiter));
    protocol.command.arguments = recv.erase(0, recv.find(delimiter) + delimiter.length());

    Session::display(protocol.user);

    return (protocol);
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
    User user;

    user.username = std::string(c_user.username);
    user.password = std::string(c_user.password);
    user.address = std::string(c_user.address);
    user.id = c_user.id;

    Session::display(user);

    return (user);
}

Commands Session::C_command_to_commands(C_Commands c_commands)
{
    Commands commands;

    commands.command = std::string(c_commands.command);
    commands.arguments = std::string(c_commands.arguments);

    return (commands);
}

bool Session::login(std::string arguments, struct User user)
{
    Session::display(user);

    this->database.uploadData(user);
    if (this->database.login(user) == this->database.SUCCESS) {
        Session::send(set_string("logged\n"));
        return (true);
    }
    Session::send(set_string("login failed\n"));

    return (false);
}

bool Session::logout(std::string arguments, struct User user)
{
    Session::display(user);
    
    Session::send(set_string("EXIT\n"));

    return (false);
}

char *Session::set_string(char *data)
{
    char *result = new char[strlen(data) + 1];

    result[strlen(data)] = '\0';
    for (int i = 0; i < strlen(data); i++) {
        result[i] = data[i];
    }

    return (result);
}

bool Session::send(char *data)
{
    /*
    socket.async_send(
        boost::asio::buffer(data, strlen(data)),
        boost::bind(
            &Session::handle_read,
            this,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
    */
   boost::system::error_code ignored_ec;

    socket.send(
        boost::asio::buffer(data, strlen(data)),
        0,
        ignored_ec
    );

    return (true);
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

    Session::send(set_string("EXIT\n"));

    return (false);
}

bool Session::call(std::string arguments, struct User user)
{
    Session::display(user);

    if (this->database.login(user) == this->database.SUCCESS) {
        Session::send(set_string("calling...\n"));
        return (true);
    }
    Session::send(set_string("user not found\n"));

    return (false);
}

bool Session::ping(std::string arguments, struct User user)
{
    Session::display(user);

    Session::send(set_string("pong\n"));

    return (false);
}

bool Session::close_server(std::string arguments, struct User user)
{
    Session::display(user);

    if (user.username == "admin" && user.password == "admin") {
        Session::send(set_string("user authorized\n"));
        Session::close_socket();
    } else {
        Session::send(set_string("user not authorized\n"));
    }

    return (false);
}
