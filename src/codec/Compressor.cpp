/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Encoder
*/

#include "codec.hpp"

Codec::Encoder::Encoder(int frameSize)
{
    state = opus_encoder_create(12000, 1, OPUS_APPLICATION_VOIP, &error_code);
    
    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");
    
    opus_encoder_ctl(state, OPUS_SET_BITRATE(64000));
    frameSize = frameSize;
}

Codec::Encoder::~Encoder()
{
}

Codec::Decoder::Decoder(int sampleRate, std::string fileName)
{
    state = opus_decoder_create(sampleRate, CHANNELS, &error_code);

    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");

    fileOutput = fopen(fileName.c_str(), "r");

    if (fileOutput == NULL)
        fprintf(stderr, "failed to open input file: %s\n", strerror(errno));
}

Codec::Decoder::~Decoder()
{
}

int Codec::Encoder::EncodeAudioStream(const float *inputData)
{
    // TODO : replace 500000...  
    opus_int16 pcm = frameSize * sizeof(opus_int16);
    unsigned char *output = static_cast<unsigned char *>(calloc(500000, sizeof(unsigned char)));
    int outputSize = opus_encode_float(this->state, inputData, frameSize, output, 500000);

    for (int i = 0; i < outputSize; i++)
        outputData.push_back(output[i]);
    free(output);
    return outputSize;
}

std::vector<unsigned char> Codec::Encoder::getOuput()
{
    return outputData;
}
