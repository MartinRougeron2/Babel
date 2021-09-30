/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Compressing
*/

#ifndef COMPRESSOR_HPP_
#define COMPRESSOR_HPP_

#include <opus.h>

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <vector>
#include <string>


namespace Codec
{
    typedef std::vector<unsigned char> PacketDataFormat;
    typedef float * SoundFormat;

    #define CHANNELS 2
    #define MAX_FRAME_SIZE 2000
    #define FRAME_COUNT 256

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

}; // namespace Codec

#endif /* !COMPRESSOR_HPP_ */
