/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Aportaudio
*/

#ifndef APORTAUDIO_HPP_
#define APORTAUDIO_HPP_

#include "portaudio.h"
#include "iostream"

class Aportaudio {
    public:
        Aportaudio();
        ~Aportaudio();
        void start_recording();
        void stop_recording();

        void start_listent();
        void stop_listent();
    protected:
    private:
        PaStreamParameters inputParam;
        PaStreamParameters outputParam;
        PaStream *inputStream;
        PaStream *outputStream;
};

#endif /* !APORTAUDIO_HPP_ */
