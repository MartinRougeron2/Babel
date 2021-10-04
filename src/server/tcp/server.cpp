/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** server.cpp
*/

#include "server/TCP.hpp"

// CHAT SERVER

chat_server::chat_server(boost::asio::io_service &io_service, const tcp::endpoint &endpoint) : acceptor_(io_service, endpoint), socket_(io_service)
{
    /*
    std::string s = socket_.remote_endpoint().address().to_string();
    std::cout << s << std::endl;
    */
    this->handler = Handler();

    chat_server::do_accept();
}

chat_server::~chat_server()
{
    return;
}

void chat_server::do_accept()
{
    this->acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
        if (!ec) {
            std::make_shared<chat_session>(std::move(socket_), room_, this->handler)->start();
        }

        do_accept();
    });
}

// CHAT SESSION

chat_session::chat_session(tcp::socket socket, chat_room &room, Handler handler) : socket_(std::move(socket)), room_(room)
{
    this->handler = handler;

    return;
}

chat_session::~chat_session()
{
    return;
}

void chat_session::start()
{
    this->room_.join(shared_from_this());
    do_read_header();
}

void chat_session::deliver(const chat_message &msg)
{
    bool write_in_progress = !write_msgs_.empty();

    write_msgs_.push_back(msg);
    if (!write_in_progress) {
        do_write();
    }
}

void chat_session::do_read_header()
{
    auto self(shared_from_this());

    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length), [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec && read_msg_.decode_header()) {
            do_read_body();
        } else {
            room_.leave(shared_from_this());
        }
    });
}

void chat_session::do_read_body()
{
    auto self(shared_from_this());

    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()), [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec) {
            room_.deliver(read_msg_);
            do_read_header();
        } else {
            room_.leave(shared_from_this());
        }
    });
}

void chat_session::do_write()
{
    auto self(shared_from_this());

    boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()), [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec) {
            write_msgs_.pop_front();
            if (!write_msgs_.empty()) {
                do_write();
            }
        } else {
            room_.leave(shared_from_this());
        }
    });
}

// CHAT MESSAGE

chat_message::chat_message() : body_length_(0)
{
    return;
}

chat_message::~chat_message()
{
    return;
}

char *chat_message::data()
{
    std::string data(this->data_);

    data = data.substr(0, data.find('\n'));
    std::cout << data << std::endl;

    std::cout << "command: '" << data << "'" << std::endl;
    if (this->handler.mapped.find(data) != this->handler.mapped.end()) {
        std::cout << "command found" << std::endl;
        this->handler.mapped.at(data);
    } else
        std::cout << "command not found" << std::endl;

    return (this->data_);
}

std::size_t chat_message::length()
{
    return (this->header_length + this->body_length_);
}

char *chat_message::body()
{
    return (this->data_ + this->header_length);
}

std::size_t chat_message::body_length()
{
    return (this->body_length_);
}

void chat_message::body_length(std::size_t new_length)
{
    this->body_length_ = new_length;

    if (this->body_length_ > this->max_body_length)
        this->body_length_ = this->max_body_length;
}

bool chat_message::decode_header()
{
    char header[this->header_length + 1] = "";

    std::strncat(header, this->data_, this->header_length);
    this->body_length_ = std::atoi(header);

    if (body_length_ > max_body_length) {
        body_length_ = 0;
        return (false);
    }

    return (true);
}

void chat_message::encode_header()
{
    char header[header_length + 1] = "";

    std::sprintf(header, "%4d", static_cast<int>(this->body_length_));
    std::memcpy(this->data_, header, this->header_length);
}

// CHAT ROOM

void chat_room::join(chat_participant_ptr participant)
{
    std::cout << USER_JOINED << participant << std::endl;

    this->participants_.insert(participant);
    for (auto msg: recent_msgs_)
        participant->deliver(msg);
}

void chat_room::leave(chat_participant_ptr participant)
{
    std::cout << USER_LEFT << participant << std::endl;
    this->participants_.erase(participant);
}

void chat_room::deliver(const chat_message &msg)
{
    return;
}
