/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "server/TcpServer.hpp"

#include "Colors.hpp"

#include "security.hpp"

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
    std::cout 
      colors::blue << WAIT << "closing socket..." << colors::reset << std::endl;
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
    S_Protocol response;
    std::string raw;

    if (!err) {
        std::cout << "received: " << std::endl;
        raw = security::decoder(this->buffer);
        response = TcpSession::decode(raw);
        std::cout << "command: " << response.command.command << std::endl;
        if (this->mapped.find(response.command.command) != this->mapped.end()) {
            (this->*this->mapped.at(response.command.command))(response.command.arguments, response.user);
        } else if (this->getter.find(response.command.command) != this->getter.end()) {
            (this->*this->getter.at(response.command.command))(response.command.arguments);
        } else {
            TcpSession::send("command not found");
        }
        socket.async_read_some(
            boost::asio::buffer(
                this->buffer,
                max_length
            ),
            boost::bind(
                &TcpSession::handleRead,
                this,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred
            )
        );
        this->buffer.assign(0);
    } else if (err == boost::asio::error::eof || err == boost::asio::error::connection_reset) {
        std::cerr << colors::magenta << DONE << "A client left" << colors::reset << std::endl;
    } else {
        std::cerr << colors::red << FAIL << "err (recv): " << err.message() << colors::reset << std::endl;
        TcpSession::close_socket();
    }
}

S_Protocol TcpSession::decode(std::string recv)
{
    std::cout << recv << std::endl;
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

    // GET COMMAND
    protocol.command.command = recv.substr(0, recv.find(delimiter));
    protocol.command.arguments = recv.erase(0, recv.find(delimiter) + delimiter.length());

    TcpSession::display(protocol.user);
    this->buffer.assign(0);
    return (protocol);
}

bool TcpSession::send(const char *data)
{
    boost::system::error_code ignored_ec;
    boost::array<std::bitset<6>, max_length> encoded = security::encoder(std::string(data));

    socket.send(
        boost::asio::buffer(
            encoded,
            max_length
        ),
        0,
        ignored_ec
    );

    return (true);
}

void TcpSession::display(UserApp user)
{
    std::cout << "-----------" << std::endl;
    std::cout << "Username:  " << user.username << std::endl;
    std::cout << "Password:  " << user.password << std::endl;
    std::cout << "Address:   " << user.address << std::endl;
    std::cout << "LHost:     " << socket.local_endpoint() << std::endl;
    std::cout << "Socket:    " << socket.remote_endpoint() << std::endl;
    std::cout << "-----------" << std::endl;
}

bool TcpSession::login(std::string arguments, UserApp user)
{
    this->database.uploadData(user);
    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send(std::to_string(user.id).c_str());
        return (true);
    }
    if (this->database.login(user) == this->database.BAD_PASSWORD) {
        TcpSession::send("BAD_PASSWORD");
        return (false);
    }
    TcpSession::send("login failed");
    return (false);
}

bool TcpSession::logout(std::string arguments, UserApp user)
{
    TcpSession::display(user);
    TcpSession::send("EXIT");

    return (false);
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

    TcpSession::send("EXIT");

    return (false);
}

bool TcpSession::call(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send("calling...");
        return (true);
    }
    TcpSession::send("user not found");
    this->mtx->lock();
    this->voiceServer->join(user.address, user.id);
    this->mtx->unlock();

    return (false);
}

bool TcpSession::ping(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    TcpSession::send("pong");

    return (false);
}

bool TcpSession::accept(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    TcpSession::send("accepted");

    return (false);
}

bool TcpSession::refuse(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    TcpSession::send("refused");

    return (false);
}

bool TcpSession::add(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (TcpSession::check_linked(arguments, user) == false) {
        if (this->database.linkUser(user.username, arguments) == true) {
            TcpSession::send("true");
            return (true);
        }
        TcpSession::send("false1");
        return (false);
    }
    TcpSession::send("false");

    return (false);
}

bool TcpSession::remove(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (TcpSession::check_linked(arguments, user) == true) {
        this->database.unlinkUser(user.username, arguments);
        TcpSession::send("true");
        return (true);
    }
    TcpSession::send("false");
    return (false);
}

bool TcpSession::check_user(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);

    if (this->database.login(user) == this->database.SUCCESS) {
        TcpSession::send("true");
        return (true);
    }

    TcpSession::send("false");

    return (false);
}

UserApp TcpSession::get_user_by_id(std::string address)
{
    UserApp failed;

    failed.address = EMPTY;
    failed.id = -1;
    failed.password = EMPTY;
    failed.username = EMPTY;

    for (auto i = this->users.begin(); i != this->users.end(); i++) {
        if (i->first == std::stoi(address))
            return (i->second);
    }

    return (failed);
}

UserApp TcpSession::get_user(std::string username)
{
    UserApp failed;

    failed.address = EMPTY;
    failed.id = -1;
    failed.password = EMPTY;
    failed.username = EMPTY;

    for (auto i = this->users.begin(); i != this->users.end(); i++) {
        if (i->second.username == username)
            return (i->second);
    }

    return (failed);
}

bool TcpSession::check_linked(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);
    std::vector<UserApp> linked = this->database.getLinkedUser(user.username);

    if (linked.size() > 0) {
        for (auto i = linked.begin(); i != linked.end(); i++) {
            if (i->username == arguments) {
                TcpSession::send("true");
                return (true);
            }
        }
    }
    TcpSession::send("false");

    return (false);
}

bool TcpSession::close_server(std::string arguments, UserApp user)
{
    TcpSession::display(user);

    if (user.username == "admin" && user.password == "admin") {
        TcpSession::send("user authorized");
        TcpSession::close_socket();
    } else {
        TcpSession::send("user not authorized");
    }

    return (false);
}

bool TcpSession::get_users_in_call(std::string arguments, struct UserApp user)
{
    TcpSession::display(user);
    std::string userAddress = user.address.erase(user.address.find(':'), user.address.length());
    std::vector<shared_session> sessionsInCommon;
    std::string usersInSession;

    for (auto const &group : voiceServer->getAllGroups()) {
        for (auto const &session: group.second.sessions) {
            if (session.get()->remoteEndpoint.address().to_string() == user.address)
                sessionsInCommon = group.second.sessions;
        }
    }

    for (const auto &session : sessionsInCommon) {
        usersInSession += this->users[session->id].username;
        usersInSession += "\n";
    }

    this->usersincall = usersInSession;

    TcpSession::send(this->usersincall.c_str());

    return (false);
}

bool TcpSession::get_contacts(std::string arguments, struct UserApp user)
{
    std::vector<UserApp> contacts = database.getLinkedUser(user.username);
    std::string answer;

    for (auto &contact : contacts) {
        answer += contact.username + ";" + contact.address + ";" + contact.password + ";" + std::to_string(contact.id) + "\n";
    }
    if (answer == "")
        answer = "none";

    TcpSession::send(answer.c_str());

    return (true);
}