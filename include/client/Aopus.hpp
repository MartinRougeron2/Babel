/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Aopus
*/

#ifndef AOPUS_HPP_
#define AOPUS_HPP_

#include "opus.h"

class Aopus {
    public:
        Aopus();
        ~Aopus();
        opus_int32 encode(OpusEncoder *st, const opus_int16 *pcm, int frame_size, unsigned char *data, opus_int32 max_data_bytes)
        {
            return opus_encode(st, pcm, frame_size, data, max_data_bytes);
        }
        opus_int32 encode(OpusEncoder *st, const float *pcm, int frame_size, unsigned char *data, opus_int32 max_data_bytes)
        {
            return opus_encode_float(st, pcm, frame_size, data, max_data_bytes);
        }
        OpusEncoder* encoder_create(opus_int32 Fs, int channels, int application, int *error)
        {
            return opus_encoder_create(Fs, channels, application, error);
        }
        void encoder_destroy(OpusEncoder *st)
        {
            opus_encoder_destroy(st);
        }
        int encoder_init(OpusEncoder *st, opus_int32 Fs, int channels, int application)
        {
            return opus_encoder_init(st, Fs, channels, application);
        }
        int encoder_get_size(int channels)
        {
            return opus_encoder_get_size(channels);
        }
        // encoder_ctl(enc, OPUS_SET_BITRATE(bitrate));
        // encoder_ctl(enc, OPUS_SET_COMPLEXITY(complexity));
        // encoder_ctl(enc, OPUS_SET_SIGNAL(signal_type));
        // where

        // bitrate is in bits per second (b/s)
        // complexity is a value from 1 to 10, where 1 is the lowest complexity and 10 is the highest
        // signal_type is either OPUS_AUTO (default), OPUS_SIGNAL_VOICE, or OPUS_SIGNAL_MUSIC

        int encoder_ctl(OpusEncoder *st, int request)
        {
            opus_encoder_ctl(st, request);
        }

    protected:
    private:
};

#endif /* !AOPUS_HPP_ */



/*

Pa_Init
Pa_terminate

Pa_GetHostApiCount = nombre de pilote ok pour le son
Pa_GetDeviceIndex = nb haut parleur

Pa_CloseStream
Pa_GetErrorText
PaHostErrorInfo

Pa_GetSampleSize

*/