/*
 * Copyright 2018 Deniz A. Atlihan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "aaudio/AAudio.h"
#include "math.h"
#include "WaveGenerator.h"
#include <android/log.h>
#include <functional>
#include <thread>
#include <jni.h>
#include <string>

class AAudioEngine {
public:
    aaudio_result_t CreateAndOpenStream();
    aaudio_result_t CreateAndOpenStream(int sample_rate,int channel_count);
    aaudio_result_t StartStream();
    aaudio_result_t PauseStream();
    aaudio_result_t StopStream();
    aaudio_result_t FlushStream();
    void RestartStream();
    void SetWave(int sample_rate,float wave_frequency);
    void SetWaveOn(bool on);
    void SetWaveFrequency(float freq);
    void SetWaveVolume(float vol);

    void SetWaveType(int waveType);

private:
    AAudioStreamBuilder *builder;
    AAudioStream *stream;
    aaudio_result_t ChangeState(aaudio_stream_state_t inputState, aaudio_stream_state_t nextState);
    int sampleRate = 48000;
    int channelCount =1;
    WaveGenerator generator;
};
