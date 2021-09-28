/*
** EPITECH PROJECT, 2021
** babel
** File description:
** test
*/

#include "portaudio.h"
#include <iostream>
#include <string>

#define SAMPLE_RATE 48000
#define FRAMES_PER_BUFFER 512

typedef struct paData_s {
    int read;
    int write;
    float vol;
} paData_t;

class Portaudio {
    public:
        Portaudio();
        ~Portaudio();

        void openStream();

        const std::string getErrorMsg() const;

    private:
        std::string errStr;
        PaError err;

        PaStream *stream;
        paData_t data;
};

int funcCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    std::cout << "in func back" << std::endl;
    paData_t *data = (paData_t *) userData;
    float *out = (float *) output;
    unsigned int i;
    float *in = (float *) input;

    for(i = 0; i < frameCount; i++) {
        *out++ = *in++;
        *out++ = *in++;
    }
    return 0;
}
Portaudio::Portaudio()
{
    this->err = Pa_Initialize();

    if (this->err != paNoError) {
        this->errStr = Pa_GetErrorText(this->err);
        return;
    }
    this->err = Pa_OpenDefaultStream(&this->stream, 2, 2, paFloat32, SAMPLE_RATE, 256, funcCallback, &data);
    if (this->err != paNoError) {
        this->errStr = Pa_GetErrorText(this->err);
        return;
    }
    this->err = Pa_StartStream(this->stream);
}

Portaudio::~Portaudio()
{
    Pa_StopStream(this->stream);
    Pa_CloseStream(this->stream);

    err = Pa_Terminate();
    if (err != paNoError)
        this->errStr = Pa_GetErrorText(this->err);
    this->errStr = nullptr;
}

const std::string Portaudio::getErrorMsg() const
{
    return this->errStr;
}

int main(void)
{
    Portaudio p;
    while (1)
        Pa_Sleep(1000);
}
