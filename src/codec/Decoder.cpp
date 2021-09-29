/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Decoder
*/

#include "../../include/codec.hpp"

Codec::Decoder::Decoder(const int sampleRate)
{
    state = opus_decoder_create(sampleRate, CHANNELS, &error_code);

    if (error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");
    
}

Codec::Decoder::~Decoder()
{
    opus_decoder_destroy(this->state);
}

int Codec::Decoder::decodeData(const PacketDataFormat input, const int frameSize)
{
    const unsigned char *inputFormatted = &input[0];
    sound = static_cast<SoundFormat>(calloc(frameSize * CHANNELS, sizeof(float)));
    // TODO: watch 0 usage 
    return opus_decode_float(this->state, inputFormatted, input.size(), sound, frameSize, 0);
}

Codec::SoundFormat Codec::Decoder::getOutput() const
{
    return sound;
}