/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** babel
*/

#include "portaudio.h"
#include <iostream>

int main(int argc, char *argv[])
{
    PaError err = Pa_Initialize();

    if (err == -1) {
        std::cout << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return 84;
    }
    // PaDeviceIndex input = Pa_GetDefaultInputDevice();

    // if (input == paNoDevice) {
    //     std::cout << "PortAudio error input" << std::endl;
    //     return 84;
    // }
    err = Pa_Terminate();
    if (err == -1) {
        std::cout << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return 84;
    }
}