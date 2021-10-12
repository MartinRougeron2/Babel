/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Encoder
*/

#include "sound/Sound.hpp"

Sound::Encoder::Encoder()
{
    this->state = opus_encoder_create(SAMPLE_RATE, CHANNELS, OPUS_APPLICATION_VOIP, &error_code);

    if (this->error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");

    opus_encoder_ctl(this->state, OPUS_SET_BITRATE(64000));
    this->frameSize = SAMPLE_RATE;
}

Sound::Encoder::~Encoder()
{
    opus_encoder_destroy(this->state);
}

int Sound::Encoder::EncodeAudioStream(const SoundFormat inputData)
{
    unsigned char *packets = new unsigned char[FRAMES_PER_BUFFER * CHANNELS];
    const float *inputDataFormatted = &inputData[0];
    int packetsSize;

    packetsSize = opus_encode_float(this->state, inputDataFormatted, this->frameSize, packets, FRAMES_PER_BUFFER * CHANNELS);

    this->outputData.clear();
    for (size_t i = 0; i < packetsSize; i++)
        this->outputData.push_back(packets[i]);
    return packetsSize;
}

Sound::PacketDataFormat Sound::Encoder::getOuput() const
{
    return outputData;
}
