/*
** EPITECH PROJECT, 2021
** babel
** File description:
** test
*/

#include "client/Sound.hpp"

static int recordCallback(const void *input, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    data_t *data = (data_t *) userData;
    float *out = (float *) output;
    float *in = (float *) input;

    for (size_t i = 0; i < frameCount; i++) {
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
    this->err = this->audio.Initialize();

    if (this->err)
        this->errMsg = this->audio.GetErrorText(this->err);
}

Sound::~Sound()
{
    this->err = this->audio.Terminate();

    if (this->err)
        this->errMsg = this->audio.GetErrorText(this->err);
}

void Sound::init()
{
    this->err = this->audio.OpenDefaultStream(&this->stream, 1, 1, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, recordCallback, &this->data);
    if (this->err) {
        this->errMsg = this->audio.GetErrorText(this->err);
        return;
    }

    this->err = this->audio.StartStream(this->stream);
    if (this->err) {
        this->errMsg = this->audio.GetErrorText(this->err);
        return;
    }
}

std::vector<float> Sound::getMic()
{
    std::vector<float> tmp = this->data.record;

    this->data.record.clear();
    return tmp;
}

void Sound::toSpeaker(std::vector<float> sample)
{
    this->data.play.insert(this->data.play.end(), sample.begin(), sample.end() );
}

const std::string Sound::getErrorMsg() const
{
    return this->errMsg;
}
