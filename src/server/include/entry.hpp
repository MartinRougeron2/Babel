/*
** EPITECH PROJECT, 2019
** client.hpp
** File description:
** client
*/

#ifndef entry_HPP_
    #define entry_HPP_

    #include <vector>
    #include <string>
    #include <array>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>

    class entry {
        public:
            entry(void *_serv, boost::asio::ip::tcp::socket *sock);
            ~entry();

            std::string pseudo;
            std::string address;
            int port;
            boost::asio::ip::tcp::socket *socket_id;
            std::array<char, 512> buffer;
            void *serv;

            std::vector<std::string> death = {
                " has segfaulted",
                " was pummeled by syamy",
                " was pricked to death",
                " drowned",
                " experienced kinetic energy",
                " blew up",
                " fell off some vines",
                " hit the ground too hard",
                " fell from a high place",
                " fell off a ladder",
                " fell off some twisting vines",
                " fell off scaffolding",
                " fell while climbing",
                " was impaled on a stalagmite",
                " was squashed by a falling anvil",
                " was squashed by a falling block",
                " was skewered by a falling stalactite",
                " went up in flames",
                " burned to death",
                " went off with a bang",
                " tried to swim in lava",
                " was struck by lightning",
                " discovered the floor was lava",
                " was killed by magic",
                " froze to death",
                " was stung to death",
                " starved to death",
                " suffocated in a wall",
                " was squished too much",
                " was poked to death by a sweet berry bush",
                " fell out of the world",
                " withered away",
                " died from dehydration"
            };

            void procData(std::string data);
            void sendToClient(int id, std::vector<std::string> args);
            void handleData(std::string);
            void asyncReceive(void);
            void stop();
    };

#endif /* !entry_HPP_ */
