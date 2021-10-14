/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include <QtGui>
#include <QApplication>
#include "GUI/App.h"
#include "client/protocol/ClientUdp.hpp"
#include "client/sound/Sound.hpp"

using boost::asio::ip::tcp;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main()
{
    boost::asio::io_service ios;
    ClientUdp voiceClient = ClientUdp("127.0.0.1", ios);
    Sound::RecorderPlayer player;
    Sound::Codec codec(player.getSampleRate(), player.getChannelNumber(), player.getBufferSize());

    std::vector<unsigned char> encodedFrame;
    std::string voiceSave;

    player.init();

    ios.run();
    while (1) {
        encodedFrame = codec.encodeFrames(player.getMic());
        std::cout << "\033[31m";
        for (auto const &t : encodedFrame)
            std::cout << int(t) << ",";
        std::cout << "\033[0m" << std::endl;
        voiceClient.sendMessage(encodedFrame);
        player.frameToSpeaker(codec.decodeFrames(voiceClient.getMessage()));
    }

//    QApplication app(argc, argv);
//    App main_app;
//
//    main_app.show(); //show the widget and its children
    return 0;//app.exec(); // execute the application
}

#pragma clang diagnostic pop
