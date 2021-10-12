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

    class Codec
    {
        public:
            /**
             * * Create codec to encode and decode audio
             * @param sampleRate frequency of sample
             * @param sampleRate number of channels
             * @param bufferSize buffer size
             * @throw const char *
             */
            Codec(size_t sampleRate, size_t channels, size_t bufferSize);
            ~Codec();

            /**
             * Encode frames
             * @param captured frames get by mic
             * @return encoded frames
             * @throw const char *
             */
            std::vector<unsigned char> encodeFrames(std::vector<unsigned short> captured);

            /**
             * Decode frames
             * @param encoded frames encoded
             * @return decoded frames
             * @throw const char *
             */
            std::vector<unsigned short> decodeFrames(std::vector<unsigned char> encoded);

        private:
            size_t bufferSize;
            size_t channels;

            int opusErr;

            opus_int32 enc_bytes;
            opus_int32 dec_bytes;

            OpusEncoder *enc;
            OpusDecoder *dec;
    };
}; // namespace Sound

#endif /* !SOUND_HPP_ */
