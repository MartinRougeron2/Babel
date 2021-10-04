/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** TCP.hpp
*/

#ifndef CHAT_MESSAGE_HPP
    #define CHAT_MESSAGE_HPP

    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <deque>
    #include <iostream>
    #include <list>
    #include <memory>
    #include <set>
    #include <utility>
    #include <boost/asio.hpp>

    #include "Signals.hpp"
    #include "Logs.hpp"
    #include "Handler.hpp"

    #define TCP_PORT 2000

    using boost::asio::ip::tcp;

    class chat_message
    {
        public:
            enum
            {
                header_length = 4
            };

            enum
            {
                max_body_length = 512
            };

            chat_message();
            ~chat_message();

            char *data();
            char *body();

            std::size_t length();
            std::size_t body_length();
            void body_length(std::size_t);
            bool decode_header();
            void encode_header();

            Handler handler;

        private:
            char data_[header_length + max_body_length];
            std::size_t body_length_;
    };


    class chat_participant
    {
        public:
            virtual ~chat_participant() {}
            virtual void deliver(const chat_message &msg) = 0;
    };

    typedef std::shared_ptr<chat_participant> chat_participant_ptr;
    typedef std::deque<chat_message> chat_message_queue;

    class chat_room
    {
        public:
            void join(chat_participant_ptr);
            void leave(chat_participant_ptr);
            void deliver(const chat_message &);

        private:
            std::set<chat_participant_ptr> participants_;
            chat_message_queue recent_msgs_;
            enum
            {
                max_recent_msgs = 100
            };
    };

    class chat_session : public chat_participant, public std::enable_shared_from_this<chat_session>
    {
        public:
            chat_session(tcp::socket, chat_room &, Handler);
            ~chat_session();

            void start();
            void deliver(const chat_message &);

        private:
            tcp::socket socket_;
            chat_room& room_;
            chat_message read_msg_;
            chat_message_queue write_msgs_;

            Handler handler;

            void do_read_header();
            void do_read_body();
            void do_write();
    };

    class chat_server
    {
        public:
            chat_server(boost::asio::io_service &, const tcp::endpoint &);
            ~chat_server();

        private:
            tcp::acceptor acceptor_;
            tcp::socket socket_;
            chat_room room_;

            Handler handler;

            void do_accept();
    };

#endif // CHAT_MESSAGE_HPP
