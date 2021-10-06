/*
** EPITECH PROJECT, 2021
** babel
** File description:
** test
*/

#include "sound/Sound.hpp"


Sound::RecorderPlayer::RecorderPlayer()
{
}

Sound::RecorderPlayer::~RecorderPlayer()
{
    if (this->audio.IsStreamStopped(this->stream))
        this->audio.StopStream(this->stream);
    if (this->audio.IsStreamActive(this->stream))
        this->audio.CloseStream(this->stream);
    this->audio.Terminate();
}

void Sound::RecorderPlayer::init()
{
    this->channelsNb = 1;
    this->bufferSize = 480;
    this->sampleRate = 48000;

    if ((this->err = this->audio.Initialize()) != paNoError)
        throw this->audio.GetErrorText(this->err);
    if ((this->err = this->audio.OpenDefaultStream(&this->stream, this->channelsNb, this->channelsNb, paInt16, this->sampleRate, this->bufferSize, nullptr, nullptr)) != paNoError)
        throw this->audio.GetErrorText(this->err);
    if ((this->err = this->audio.StartStream(this->stream)) != paNoError)
        throw this->audio.GetErrorText(this->err);
}

void Sound::RecorderPlayer::stop()
{
    if ((this->err = this->audio.StopStream(this->stream)) != paNoError)
        throw this->audio.GetErrorText(this->err);
    if ((this->err = this->audio.CloseStream(this->stream)) != paNoError)
        throw this->audio.GetErrorText(this->err);
    if ((this->err = this->audio.Terminate()) != paNoError)
        throw this->audio.GetErrorText(this->err);
}

const std::vector<unsigned short> Sound::RecorderPlayer::getMic(void)
{
    std::vector<unsigned short> captured(this->bufferSize * this->channelsNb);

    if ((this->err = this->audio.ReadStream(this->stream, captured.data(), this->bufferSize)) != paNoError)
        throw this->audio.GetErrorText(this->err);
    return captured;
}

void Sound::RecorderPlayer::frameToSpeaker(const std::vector<unsigned short> &decoded)
{
    if ((this->err = this->audio.WriteStream(this->stream, decoded.data(), this->bufferSize)) != paNoError) {
        throw this->audio.GetErrorText(this->err);
    }
}

const size_t &Sound::RecorderPlayer::getChannelNumber() const
{
    return this->channelsNb;
}

const size_t &Sound::RecorderPlayer::getSampleRate() const
{
    return this->sampleRate;
}

const size_t &Sound::RecorderPlayer::getBufferSize() const
{
    return this->bufferSize;
}
