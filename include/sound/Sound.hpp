/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "Aportaudio.hpp"
#include <opus.h>

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
    typedef float * SoundFormat;

    #define SAMPLE_RATE 48000
    #define FRAMES_PER_BUFFER 256
    #define CHANNEL_NUMBER 1
    #define CHANNELS 2
    #define MAX_FRAME_SIZE 2000
    #define FRAME_COUNT 256

    typedef struct data_s
    {
        std::vector<float> record;
        std::vector<float> play;
    } data_t;

    class RecorderPlayer
    {
        public:
            RecorderPlayer();
            ~RecorderPlayer();

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

    // ** Codec **


    class Encoder {
        public:
            Encoder(const int);
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
            Decoder(const int sampleRate);
            ~Decoder();
            
            int decodeData(const PacketDataFormat data, const int frameSize);
            SoundFormat getOutput() const;

        protected:
        private:
            OpusDecoder *state;
            int error_code;
            SoundFormat sound;
    };


} // namespace Sound

#endif /* !SOUND_HPP_ */
