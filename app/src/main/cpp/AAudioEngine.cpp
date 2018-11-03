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


#include "AAudioEngine.h"

aaudio_data_callback_result_t WaveCallback(
        AAudioStream *stream,
        void *userData,
        void *audioData,
        int32_t numFrames) {
    ((WaveGenerator *) (userData))->Generate(static_cast<float *>(audioData), numFrames);
    return AAUDIO_CALLBACK_RESULT_CONTINUE;
}
void ErrorCallback(AAudioStream *stream,
                   void *userData,
                   aaudio_result_t error){
    if (error == AAUDIO_ERROR_DISCONNECTED){
        std::function<void(void)> restartFunction = std::bind(&AAudioEngine::RestartStream,
                                                              static_cast<AAudioEngine *>(userData));
        new std::thread(restartFunction);
    }
}

void AAudioEngine::RestartStream(){

    static std::mutex restartingLock;
    if (restartingLock.try_lock()){
        StopStream();
        StartStream();
        restartingLock.unlock();
    }
}

aaudio_result_t AAudioEngine::CreateAndOpenStream(int sample_rate, int channel_count) {
    sampleRate = sample_rate;
    channelCount = channel_count;
    return CreateAndOpenStream();
}

aaudio_result_t AAudioEngine::CreateAndOpenStream() {
    aaudio_result_t result = AAudio_createStreamBuilder(&builder);
    if (result != AAUDIO_OK) {
        return result;
    }
    AAudioStreamBuilder_setDeviceId(builder, 0);
    AAudioStreamBuilder_setDirection(builder, AAUDIO_DIRECTION_OUTPUT);
    AAudioStreamBuilder_setSharingMode(builder, AAUDIO_SHARING_MODE_SHARED);
    AAudioStreamBuilder_setSampleRate(builder, sampleRate);
    AAudioStreamBuilder_setChannelCount(builder, channelCount);
    AAudioStreamBuilder_setFormat(builder, AAUDIO_FORMAT_PCM_FLOAT);
    AAudioStreamBuilder_setDataCallback(builder, WaveCallback, &generator);
    AAudioStreamBuilder_setErrorCallback(builder, ::ErrorCallback, this);
    AAudioStreamBuilder_setPerformanceMode(builder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
    AAudioStreamBuilder_setBufferCapacityInFrames(builder, sampleRate * 0.20f);
    result  = AAudioStreamBuilder_openStream(builder, &stream);
    return result;
}

aaudio_result_t AAudioEngine::StartStream() {
    aaudio_result_t result =  AAudioStream_requestStart(stream);
    return result;
}

aaudio_result_t AAudioEngine::PauseStream() {
    aaudio_result_t result = AAudioStream_requestPause(stream);
    return result;
}

aaudio_result_t AAudioEngine::StopStream() {
    aaudio_result_t result = AAudioStream_requestStop(stream);
    return result;
}

aaudio_result_t AAudioEngine::FlushStream() {
    aaudio_result_t result = AAudioStream_requestFlush(stream);
    AAudioStreamBuilder_delete(builder);
    return result;
}

aaudio_result_t
AAudioEngine::ChangeState(aaudio_stream_state_t inputState, aaudio_stream_state_t nextState) {
    int64_t timeoutNanos = 100;
    aaudio_result_t result = AAudioStream_waitForStateChange(stream, inputState, &nextState, timeoutNanos);
    return result;
}

void AAudioEngine::SetWave(int sample_rate, float wave_frequency) {
    generator.SetGeneratorWaveFreqeuncy(wave_frequency);
    generator.SetGeneratorSampleFrequency(sample_rate);
}

void AAudioEngine::SetWaveOn(bool on) {
    generator.SetGeneratorWaveOn(on);
}

void AAudioEngine::SetWaveFrequency(float freq) {
    generator.SetGeneratorWaveFreqeuncy(freq);
}

void AAudioEngine::SetWaveVolume(float vol) {
    generator.SetGeneratorWaveVolume(vol);
}

void AAudioEngine::SetWaveType(int waveType) {
    generator.SetGeneratorWaveType(waveType);
}