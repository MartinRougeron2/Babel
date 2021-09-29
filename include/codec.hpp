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

    class Encoder {
        public:
            Encoder(int frameSize);
            ~Encoder();
            int EncodeAudioStream(const float *inputData);
            std::vector<unsigned char>getOuput();

        protected:
        private:
            OpusEncoder *state;
            int error_code;
            int frameSize;
            std::vector<unsigned char> outputData;
    };

    class Decoder {
        public:
            Decoder(int sampleRate, std::string fileName);
            ~Decoder();
            int initEncodeAudioStream(std::vector<unsigned char> data);
            void encodeAudio();

        protected:
        private:
            OpusDecoder *state;
            int error_code;
            FILE *fileOutput;
    };

    int CHANNELS = 2;
    int MAX_FRAME_SIZE = 2000;

    int FRAME_COUNT = 256;

}; // namespace Codec

#endif /* !COMPRESSOR_HPP_ */
