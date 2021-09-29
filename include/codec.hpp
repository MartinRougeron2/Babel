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

    class Encoder {
        public:
            Encoder(const int frameSize);
            ~Encoder();
            int EncodeAudioStream(const SoundFormat inputData);
            PacketDataFormat getOuput() const;

        protected:
        private:
            OpusEncoder *state;
            int error_code;
            int frameSize;
            PacketDataFormat outputData;
    };

    class Decoder {
        public:
            Decoder(const int sampleRate);
            ~Decoder();
            int decodeData(const PacketDataFormat data, const int frameSize);
            SoundFormat getOutput() const;

        protected:
        private:
            OpusDecoder *state;
            int error_code;
            FILE *fileOutput;
            SoundFormat sound;
    };

    int CHANNELS = 2;
    int MAX_FRAME_SIZE = 2000;

    int FRAME_COUNT = 256;

}; // namespace Codec

#endif /* !COMPRESSOR_HPP_ */
