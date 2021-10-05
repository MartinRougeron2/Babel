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
    opus_int32 rate;

    if (this->error_code < 0)
        fprintf(stderr, "failed to create decoder:\n");

    opus_encoder_ctl(this->state, OPUS_GET_BANDWIDTH(&rate));
    this->encoded_data_size = rate;
}

Sound::Encoder::~Encoder()
{
    opus_encoder_destroy(this->state);
}

Sound::PacketDataFormat *Sound::Encoder::EncodeAudioStream(const float *frame)
{
    Sound::PacketDataFormat *compressed_buffer = new (Sound::PacketDataFormat[this->encoded_data_size]);
    int ret = opus_encode_float(this->state, frame, 480, compressed_buffer, this->encoded_data_size);

    return compressed_buffer;
}
