/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Aportaudio.hpp"
#include "opus.h"

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

namespace Sound
{

    typedef std::vector<unsigned char> PacketDataFormat;
    typedef std::vector<float> SoundFormat;
    typedef float * opusInputType;

    #define SAMPLE_RATE 48000
    #define FRAMES_PER_BUFFER 256
    #define CHANNELS 2

    typedef struct data_s
    {
        SoundFormat record;
        SoundFormat play;
    } data_t;

    class RecorderPlayer
    {
        public:
            RecorderPlayer();
            ~RecorderPlayer();

            void init(void);

            /*
            ** Get sound via mic.
            ** @return vector of float with amplitude get by mic
            */
            SoundFormat getMic();

            /*
            ** sound to speaker.
            ** @param sample vector of float with amplitude get by mic
            ** @return vector of float with amplitude get by mic
            */
            void toSpeaker(SoundFormat sample);

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

    // ** Codec **


    class Encoder
    {
        public:
            Encoder();
            ~Encoder();

            int EncodeAudioStream(const SoundFormat);
            PacketDataFormat getOuput() const;

        protected:
        private:
            OpusEncoder *state;
            int error_code;
            int frameSize;
            PacketDataFormat outputData;
    };

    class Decoder
    {
        public:
            Decoder();
            ~Decoder();

            int decodeData(const PacketDataFormat data, const int frameSize);
            SoundFormat getOutput() const;

        protected:
        private:
            OpusDecoder *state;
            int error_code;
            SoundFormat sound;
    };

}; // namespace Sound

#endif /* !SOUND_HPP_ */
