// /*
// ** EPITECH PROJECT, 2021
// ** B-CPP-500-LYN-5-1-babel-martin.rougeron
// ** File description:
// ** Aportaudio
// */

// #include "client/Aportaudio.hpp"

// typedef struct
// {
//     float left_phase;
//     float right_phase;
// }
// paTestData;

// Aportaudio::Aportaudio()
// {
//     auto err = Pa_Initialize();
//     if (err != paNoError) {
//         std::cout << "Port Audio error initialize: " << Pa_GetErrorText(err) << std::endl;
//         return;
//     }
//     this->inputParam.device = Pa_GetDefaultInputDevice();
//     if (this->inputParam.device == paNoDevice)
//         std::cout << "No input Device" << std::endl;
//     this->inputParam.channelCount = 2;
//     this->inputParam.sampleFormat = paFloat32;
//     this->inputParam.suggestedLatency = Pa_GetDeviceInfo(inputParam.device)->defaultLowInputLatency;
//     this->inputParam.hostApiSpecificStreamInfo = NULL;
//     this->outputParam.device = Pa_GetDefaultInputDevice();
//     if (this->outputParam.device == paNoDevice)
//         std::cout << "No input Device" << std::endl;
//     this->outputParam.channelCount = 2;
//     this->outputParam.sampleFormat = paFloat32;
//     this->outputParam.suggestedLatency = Pa_GetDeviceInfo(outputParam.device)->defaultLowInputLatency;
//     this->outputParam.hostApiSpecificStreamInfo = NULL;
// }

// Aportaudio::~Aportaudio()
// {
//     Pa_CloseStream(inputStream);
//     Pa_CloseStream(outputStream);
//     auto err = Pa_Terminate();
//     if (err != paNoError) {
//         std::cout << "Port Audio error terminate: " << Pa_GetErrorText(err) << std::endl;
//         return;
//     }
// }

// static int PaStreamCallback(const void *inputBuffer, void *outputBuffer,
//                            unsigned long framesPerBuffer,
//                            const PaStreamCallbackTimeInfo* timeInfo,
//                            PaStreamCallbackFlags statusFlags,
//                            void *userData )
// {
//     /* Cast data passed through stream to our structure. */
//     paTestData *data = (paTestData*)userData;
//     float *out = (float*)outputBuffer;
//     unsigned int i;
//     (void) inputBuffer; /* Prevent unused variable warning. */
//     for(i = 0; i < framesPerBuffer; i++)
//     {
//         *out = data->left_phase;  /* left */
//         out++;
//         *out = data->right_phase;  /* right */
//         out++;
//         /* Generate simple sawtooth phaser that ranges between -1.0 and 1.0. */
//         data->left_phase += 0.01f;
//         /* When signal reaches top, drop back down. */
//         if( data->left_phase >= 1.0f ) data->left_phase -= 2.0f;
//         /* higher pitch so we can distinguish left and right. */
//         data->right_phase += 0.03f;
//         if( data->right_phase >= 1.0f ) data->right_phase -= 2.0f;
//     }
//     return 0;
// }

// void Aportaudio::start_listent()
// {
//     auto err = Pa_OpenStream(&this->outputStream,
//                             NULL,
//                             &this->outputParam,
//                             44100,
//                             256,
//                             paClipOff,
//                             PaStreamCallback,
//                             this);
//     if (err != paNoError) {
//         std::cout << "error opening input stream" << std::endl;
//     }
//     err = Pa_StartStream(this->outputStream);
//     if (err != paNoError) {
//         std::cout << "error starting input stream" << std::endl;
//     }
// }

// void Aportaudio::stop_listent()
// {
//     auto err = Pa_StopStream(this->outputStream);
//     if (err != paNoError) {
//         std::cout << "error stoping input stream" << std::endl;
//     }
// }

// void Aportaudio::start_recording()
// {
//     auto err = Pa_OpenStream(&this->inputStream,
//                             &this->inputParam,
//                             NULL,
//                             44100,
//                             256,
//                             0,
//                             PaStreamCallback,
//                             this);
//     if (err != paNoError) {
//         std::cout << "error opening input stream" << std::endl;
//     }
//     err = Pa_StartStream(this->inputStream);
//     if (err != paNoError) {
//         std::cout << "error starting input stream" << std::endl;
//     }
// }

// void Aportaudio::stop_recording()
// {
//     auto err = Pa_StopStream(this->inputStream);
//     if (err != paNoError) {
//         std::cout << "error stoping input stream" << std::endl;
//     }
// }
