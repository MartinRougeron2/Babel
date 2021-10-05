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
    typedef unsigned char PacketDataFormat;
    typedef std::vector<float> SoundFormat;
    typedef float * opusInputType;

    #define SAMPLE_RATE 48000
    #define FRAMES_PER_BUFFER 256
    #define CHANNELS 1

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

            Aportaudio audio;
        private:

            PaStream *stream;

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

            Sound::PacketDataFormat *EncodeAudioStream(const float *frame);

        protected:
        private:
            OpusEncoder *state;
            int error_code;
            int frameSize;
            PacketDataFormat outputData;
            opus_int32 encoded_data_size;
    };

    class Decoder
    {
        public:
            Decoder();
            ~Decoder();

            Sound::SoundFormat decodeData(const unsigned char *data);

        protected:
        private:
            OpusDecoder *state;
            int error_code;
            SoundFormat sound;
            opus_int32 encoded_data_size;
    };

}; // namespace Sound

#endif /* !SOUND_HPP_ */
