/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Encoder
*/

#include "../../include/codec.hpp"

Codec::Encoder::Encoder(const int frameSize)
{
    // TODO: replace 12000 -> sampling rate, 1 is channels, 64000 -> Bitrate
    state = opus_encoder_create(12000, CHANNELS, OPUS_APPLICATION_VOIP, &error_code);
    
    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");
    
    opus_encoder_ctl(state, OPUS_SET_BITRATE(64000));
    this->frameSize = frameSize;
}

Codec::Encoder::~Encoder()
{
    opus_encoder_destroy(this->state);
}

int Codec::Encoder::EncodeAudioStream(const SoundFormat inputData)
{
    // TODO : replace 500000...  
    unsigned char *packets = new unsigned char[500000];
    int packetsSize = opus_encode_float(this->state, inputData, frameSize, packets, 500000);

    for (int i = 0; i < packetsSize; i++)
        outputData.push_back(packets[i]);
    free(packets);
    return packetsSize;
}

Codec::PacketDataFormat Codec::Encoder::getOuput() const
{
    return outputData;
}
