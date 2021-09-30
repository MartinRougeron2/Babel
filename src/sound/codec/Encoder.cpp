/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Encoder
*/

#include "sound/Sound.hpp"

Sound::Encoder::Encoder(const int frameSize)
{
    // TODO: replace 12000 -> sampling rate, 1 is channels, 64000 -> Bitrate
    state = opus_encoder_create(12000, CHANNELS, OPUS_APPLICATION_VOIP, &error_code);
    
    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");
    
    opus_encoder_ctl(state, OPUS_SET_BITRATE(64000));
    this->frameSize = frameSize;
}

Sound::Encoder::~Encoder()
{
    opus_encoder_destroy(this->state);
}

int Sound::Encoder::EncodeAudioStream(const SoundFormat inputData)
{
    // TODO : replace 500000...  
    unsigned char *packets = new unsigned char[500000];
    const opusInputType inputDataFormatted = &inputData[0];
    int packetsSize;
    
    packetsSize = opus_encode_float(this->state, inputDataFormatted, frameSize, packets, 500000);

    outputData = &packets[0];
    return packetsSize;
}

Sound::PacketDataFormat Sound::Encoder::getOuput() const
{
    return outputData;
}
