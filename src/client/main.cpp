/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** main.cpp
*/

#include <QtGui>
#include <QApplication>
#include "GUI/App.h"

int tcpMain();

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    App main_app;
    // boost::asio::io_service io_service;

    // signals::handler();
    // TCP client_tcp = TCP();
    // try
    // {
    //     tcp::resolver resolver(io_service);
    //     auto endpoint_iterator = resolver.resolve({ argv[1], argv[2] });
    //     chat_client c(io_service, endpoint_iterator);

    //     std::thread t([&io_service](){ io_service.run(); });

    //     char line[chat_message::max_body_length + 1];

    //     while (std::cin.getline(line, chat_message::max_body_length + 1))
    //     {
    //         chat_message msg;
    //         msg.body_length(std::strlen(line));
    //         std::memcpy(msg.body(), line, msg.body_length());
    //         msg.encode_header();
    //         c.write(msg);
    //     }
    //     c.close();
    //     t.join();
    // }
    // catch (std::exception& e)
    // {
    //     std::cerr << "Exception: " << e.what() << "\n";
    // }

    tcpMain();
    main_app.show(); //show the widget and its children
    return app.exec(); // execute the application
}


/*
int opusErr;
PaError paErr;
std::string s;

int const channels = 2;
int const bufferSize = 480;
int const sampleRate = 48000;
int const durationSeconds = 5;

opus_int32 enc_bytes;
opus_int32 dec_bytes;
int framesProcessed = 0;

std::vector<unsigned short> captured(bufferSize * channels);
std::vector<unsigned short> decoded(bufferSize * channels);
// * 2: byte count, 16 bit samples
std::vector<unsigned char> encoded(bufferSize * channels * 2);

// initialize opus
OpusEncoder* enc = opus_encoder_create(
    sampleRate, channels, OPUS_APPLICATION_AUDIO, &opusErr);
if (opusErr != OPUS_OK)
{
    std::cout << "opus_encoder_create failed: " << opusErr << "\n";
    std::getline(std::cin, s);
    return 1;
}

OpusDecoder* dec = opus_decoder_create(
    sampleRate, channels, &opusErr);
if (opusErr != OPUS_OK)
{
    std::cout << "opus_decoder_create failed: " << opusErr << "\n";
    std::getline(std::cin, s);
    return 1;
}

// initialize portaudio
if ((paErr = Pa_Initialize()) != paNoError)
{
    std::cout << "Pa_Initialize failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

PaStream* stream = nullptr;
if ((paErr = Pa_OpenDefaultStream(&stream, channels, channels, paInt16, sampleRate, bufferSize, nullptr, nullptr)) != paNoError) {
    std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

// start stream
if ((paErr = Pa_StartStream(stream)) != paNoError)
{
    std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

// capture, encode, decode & render durationSeconds of audio
while (framesProcessed < sampleRate * durationSeconds) {
    if ((paErr = Pa_ReadStream(stream, captured.data(), bufferSize)) != paNoError) {
        std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const*>(captured.data()), 480, encoded.data(), encoded.size())) < 0) {
        std::cout << "opus_encode failed: " << enc_bytes << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    if ((dec_bytes = opus_decode(dec, encoded.data(), enc_bytes, reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0) {
        std::cout << "opus_decode failed: " << dec_bytes << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    if ((paErr = Pa_WriteStream(stream, decoded.data(), bufferSize)) != paNoError) {
        std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    framesProcessed += bufferSize;
}

// stop stream
if ((paErr = Pa_StopStream(stream)) != paNoError)
{
    std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

// cleanup portaudio
if ((paErr = Pa_CloseStream(stream)) != paNoError)
{
    std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

if ((paErr = Pa_Terminate()) != paNoError)
{
    std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(paErr) << "\n";
    std::getline(std::cin, s);
    return 1;
}

// cleanup opus
opus_decoder_destroy(dec);
opus_encoder_destroy(enc);
*/
