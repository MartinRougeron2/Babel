/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "client/Aportaudio.hpp"

#include <iostream>
#include <string>
#include <vector>

#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 256
#define CHANNEL_NUMBER 1

typedef struct data_s {
    std::vector<float> record;
    std::vector<float> play;
} data_t;

class Sound {
    public:
        Sound();
        ~Sound();

        void init(void);
        std::vector<float> getMic();
        void toSpeaker(std::vector<float> sample);

        const std::string getErrorMsg() const;

    private:
        Aportaudio audio;

        PaStream *stream;
        PaStreamParameters input;
        PaStreamParameters output;

        data_t data;
        PaError err;
        std::string errMsg;
};

#endif /* !SOUND_HPP_ */
