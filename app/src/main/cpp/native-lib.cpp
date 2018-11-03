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


extern "C" {
AAudioEngine *engine =  new AAudioEngine();

JNIEXPORT void JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_SetWaveType(JNIEnv *env, jobject instance,
                                                                      jint type) {
    engine->SetWaveType(type);
}

JNIEXPORT void JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_SetFrequnecy(JNIEnv *env, jobject instance,
                                                                       jfloat freq) {
    engine->SetWaveFrequency(freq);
}

JNIEXPORT void JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_SetVolume(JNIEnv *env, jobject instance,
                                                                    jfloat vol) {
    engine->SetWaveVolume(vol);
}

JNIEXPORT void JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_SetTone(JNIEnv *env, jobject instance,
                                                                  jboolean on) {
    engine->SetWaveOn(on);
}

JNIEXPORT void JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_FlushStream(JNIEnv *env, jobject instance) {
    engine->FlushStream();
}

JNIEXPORT jint JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_CreateEngine(JNIEnv *env, jobject instance,
                                                                       jfloat freq, jfloat vol) {
    return engine->CreateAndOpenStream();
}

JNIEXPORT jint JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_StartEngine(JNIEnv *env, jobject instance) {
    return engine->StartStream();
}

JNIEXPORT jint JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_PauseEngine(JNIEnv *env,jobject instance) {
    return engine->PauseStream();
}

JNIEXPORT jint JNICALL
Java_com_denizoncoding_aaudiowavegenerator_MainActivity_StopEngine(JNIEnv *env,jobject instance) {
    return engine->StopStream();
}

}