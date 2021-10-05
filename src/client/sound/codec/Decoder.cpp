/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Decoder
*/

#include "sound/Sound.hpp"


Sound::Decoder::Decoder()
{
    state = opus_decoder_create(SAMPLE_RATE, CHANNELS, &error_code);
    opus_int32 rate;

    if (error_code != OPUS_OK)
        fprintf(stderr, "failed to create decoder:\n");
    opus_decoder_ctl(this->state, OPUS_GET_BANDWIDTH(&rate));
    this->encoded_data_size = rate;
}

Sound::Decoder::~Decoder()
{
    opus_decoder_destroy(this->state);
}

Sound::SoundFormat Sound::Decoder::decodeData(const unsigned char *data)
{
    int ret;
    float *frame = new (float[SAMPLE_RATE * CHANNELS]);
    std::vector<float> sound;

    opus_packet_get_nb_channels(data);
    ret = opus_decode_float(this->state, data, this->encoded_data_size, frame, 480, 0);

    for (size_t i = 0; i < SAMPLE_RATE * CHANNELS; i++)
        sound.push_back(frame[i]);
    delete frame;
    return sound;
}
