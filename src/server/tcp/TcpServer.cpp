/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "server/TcpServer.hpp"

#include "Colors.hpp"

TcpServer::TcpServer(boost::asio::io_service &ios, short port) : ios(ios),
acceptor(ios, tcp::endpoint(tcp::v4(), port))
{
    this->voiceServer = new UdpServer(ios);
    std::shared_ptr<TcpSession> session = std::make_shared<TcpSession>(ios,
                                                                       this->voiceServer,
                                                                       &this->mtx);
    acceptor.async_accept(
        session->getSocket(),
        boost::bind(
            &TcpServer::handle_accept,
            this,
            session,
            boost::asio::placeholders::error
        )
    );
}

void TcpServer::handle_accept(std::shared_ptr<TcpSession> session, const
boost::system::error_code &err)
{
    if (!err) {
        session->start();
        session = std::make_shared<TcpSession>(ios, voiceServer, &mtx);
        acceptor.async_accept(
            session->getSocket(),
            boost::bind(
                &TcpServer::handle_accept,
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

TcpSession::TcpSession(boost::asio::io_service &ios, UdpServer *voiceServer_, std::mutex *mtx_) :
socket(ios)
{
    this->database = Asqlite3();
    this->voiceServer = voiceServer_;
    this->mtx = mtx_;
    return;
}

tcp::socket &TcpSession::getSocket()
{
    return socket;
}

void TcpSession::close_socket()
{
    std::cout << colors::blue << WAIT << "closing socket..." << colors::reset << std::endl;
    try {
        TcpSession::getSocket().close();
    } catch (std::exception &e) {
        std::cout << colors::red << FAIL << "error in closing socket " << e.what() << colors::reset << std::endl;
        return;
    }
    std::cout << colors::green << DONE << "socket closed" << colors::reset << std::endl;
    exit(0);
}

void TcpSession::start()
{
    socket.async_read_some(
        //boost::asio::buffer(this->recv, max_length),
        boost::asio::buffer(this->buffer, max_length),
        boost::bind(
            &TcpSession::handleRead,
            this,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}

void TcpSession::handleRead(std::shared_ptr<TcpSession> &s, const
boost::system::error_code &err, std::size_t bytes_transferred)
{
    // FIX: Bad Address
    S_Protocol response;

    if (!err) {
        /*
        this->recv_user = TcpSession::C_user_to_user(this->recv->user);
        this->recv_commands = TcpSession::C_command_to_commands
         (this->recv->command);

        if (this->mapped.find(this->recv_commands.command) != this->mapped.end()) {
            std::cout << colors::cyan << DONE << "command found: " << this->recv_commands.command << colors::reset << std::endl;
            (this->*this->mapped.at(this->recv_commands.command))(this->recv_commands.arguments, this->recv_user);
        } else {
            std::cout << colors::yellow << FAIL << "command not found: " << this->recv_commands.command << colors::reset << std::endl;
        }
        */
       std::cout << this->buffer << std::endl;
        response = TcpSession::decode(this->buffer);
        if (this->mapped.find(response.command.command) != this->mapped.end()) {
            (this->*this->mapped.at(response.command.command))(response.command.arguments, response.user);
        } else {
            TcpSession::send(set_string("command not found"));
        }
        socket.async_read_some(
            boost::asio::buffer(this->buffer, max_length),
            boost::bind(
                &TcpSession::handleRead,
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
        TcpSession::close_socket();
    }
}

S_Protocol TcpSession::decode(std::string recv)
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

    TcpSession::display(protocol.user);

    return (protocol);
}

void TcpSession::display(UserApp  user)
{
    std::cout << "-----------" << std::endl;
    std::cout << "Username:  " << user.username << std::endl;
    std::cout << "Password:  " << user.password << std::endl;
    std::cout << "LHost:     " << socket.local_endpoint() << std::endl;
    std::cout << "Socket:    " << socket.remote_endpoint() << std::endl;
    std::cout << "-----------" << std::endl;
}

UserApp  TcpSession::C_user_to_user(C_User c_user)
{
    UserApp user;

    user.username = std::string(c_user.username);
    user.password = std::string(c_user.password);
    user.address = std::string(c_user.address);
    user.id = c_user.id;
    TcpSession::display(user);
    return (user);
}

Commands TcpSession::C_command_to_commands(C_Commands c_commands)
{
    Commands commands;

    commands.command = std::string(c_commands.command);
    commands.arguments = std::string(c_commands.arguments);

    return (commands);
}

bool TcpSession::login(std::string arguments, UserApp user)
{
    this->database.uploadData(user);
    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send(set_string(std::to_string(user.id).c_str()));
        return (true);
    }
    if (this->database.login(user) == this->database.BAD_PASSWORD) {
        TcpSession::send(set_string("BAD_PASSWORD"));
        return (false);
    }
    TcpSession::send(set_string("login failed"));
    return (false);
}

bool TcpSession::logout(std::string arguments, UserApp user)
{
    TcpSession::display(user);
    TcpSession::send(set_string("EXIT"));

    return (false);
}

char *TcpSession::set_string(char const *data)
{
    char *result = new char[std::strlen(data) + 1];

    result[std::strlen(data)] = '\0';
    for (int i = 0; i < std::strlen(data); i++) {
        result[i] = data[i];
    }

    return (result);
}

bool TcpSession::send(char *data)
{
    /*
    socket.async_send(
        boost::asio::buffer(data, strlen(data)),
        boost::bind(
            &TcpSession::handle_read,
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

bool TcpSession::join(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    std::cout << colors::green << DONE << "joinned" << colors::reset << std::endl;

    return (false);
}

bool TcpSession::hangup(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    TcpSession::send(set_string("EXIT"));

    return (false);
}

bool TcpSession::call(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send(set_string("calling..."));
        return (true);
    }
    TcpSession::send(set_string("user not found"));
    this->mtx->lock();
    this->voiceServer->join(user.address);
    this->mtx->unlock();

    return (false);
}

bool TcpSession::ping(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    TcpSession::send(set_string("pong"));

    return (false);
}

bool TcpSession::accept(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    TcpSession::send(set_string("accepted"));

    return (false);
}

bool TcpSession::refuse(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    TcpSession::send(set_string("refused"));

    return (false);
}

bool TcpSession::add(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (TcpSession::check_linked(arguments, user) == false) {
        if (this->database.linkUser(user.username, arguments) == true) {
            TcpSession::send(set_string("true"));
            return (true);
        }
        TcpSession::send(set_string("false"));
        return (false);
    }
    TcpSession::send(set_string("false"));

    return (false);
}

bool TcpSession::remove(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (TcpSession::check_linked(arguments, user) == true) {
        // this->database.unlinkUser(user.username, arguments);
        TcpSession::send(set_string("true"));
        return (true);
    }
    TcpSession::send(set_string("false"));
    return (false);
}

bool TcpSession::check_user(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send(set_string("true"));
        return (true);
    }

    TcpSession::send(set_string("false"));

    return (false);
}

bool TcpSession::check_linked(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);
    std::vector<UserApp> linked = this->database.getLinkedUser(user.username);

    if (linked.size() > 0) {
        for (auto i = linked.begin(); i != linked.end(); i++) {
            if (i->username == arguments) {
                TcpSession::send(set_string("true"));
                return (true);
            }
        }
    }
    TcpSession::send(set_string("false"));

    return (false);
}

bool TcpSession::close_server(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    if (user.username == "admin" && user.password == "admin") {
        TcpSession::send(set_string("user authorized"));
        TcpSession::close_socket();
    } else {
        TcpSession::send(set_string("user not authorized"));
    }

    return (false);
}
