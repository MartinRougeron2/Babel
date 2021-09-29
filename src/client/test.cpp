/*
** EPITECH PROJECT, 2021
** babel
** File description:
** test
*/

#include "portaudio.h"
#include <iostream>
#include <string>
#include <vector>

#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 256
#define CHANNEL_NUMBER 1

/*
TODO ABSTRACTION PORTAUDIO (pouvoir utiliser une autre lib facilement)
 */

typedef struct data_s {
    std::vector<float> record;
    std::vector<float> play;
} data_t;

class Sound {
    public:
        Sound();
        ~Sound();

        std::vector<float> getSound();
        void putSound(std::vector<float> sample);

        const std::string getErrorMsg() const;

    private:
        std::string errStr;
        PaError err;

        PaStream *stream;
        PaStreamParameters input;
        PaStreamParameters output;

        data_t data;
};

static int recordCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    data_t *data = (data_t *) userData;
    float *out = (float *) output;
    float *in = (float *) input;

    for (unsigned int i = 0; i < frameCount; i++) {
        data->record.push_back(*in++);
        if (!data->play.empty()) {
            *out++ = data->play[0];
            data->play.erase(data->play.begin());
        }
    }
    return 0;
}

Sound::Sound()
{
    this->err = Pa_Initialize();

    if (this->err != paNoError) {
        this->errStr = Pa_GetErrorText(this->err);
        return;
    }
    Pa_OpenDefaultStream(&this->stream, 1, 1, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, recordCallback, &this->data);
    this->err = Pa_StartStream(this->stream);
}

Sound::~Sound()
{
    Pa_StopStream(this->stream);
    Pa_CloseStream(this->stream);

    err = Pa_Terminate();
    if (err != paNoError)
        this->errStr = Pa_GetErrorText(this->err);
    this->errStr = nullptr;
}

std::vector<float> Sound::getSound()
{
    std::vector<float> tmp = this->data.record;

    this->data.record.clear();
    return tmp;
}

void Sound::putSound(std::vector<float> sample)
{
    this->data.play.insert(this->data.play.end(), sample.begin(), sample.end() );
}

const std::string Sound::getErrorMsg() const
{
    return this->errStr;
}

int main(void)
{
    Sound p;

    while (1) {
        Pa_Sleep(1000);
        p.putSound(p.getSound());
    }
}
