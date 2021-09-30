/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Decoder
*/

#include "sound/Sound.hpp"


Sound::Decoder::Decoder(const int sampleRate)
{
    state = opus_decoder_create(sampleRate, CHANNELS, &error_code);

    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");
    
}

Sound::Decoder::~Decoder()
{
    opus_decoder_destroy(this->state);
}

int Sound::Decoder::decodeData(const PacketDataFormat input, const int frameSize)
{
    const unsigned char *inputFormatted = &input[0];
    Sound::opusInputType soundFormatted = static_cast<Sound::opusInputType>(calloc(frameSize * CHANNELS, sizeof(float)));
    int packetsSize;
    // TODO: watch 0 usage 
    packetsSize = opus_decode_float(this->state, inputFormatted, input.size(), soundFormatted, frameSize, 0);
    
    sound = {soundFormatted, soundFormatted + packetsSize};
    
    return packetsSize;
}

Sound::SoundFormat Sound::Decoder::getOutput() const
{
    return sound;
}