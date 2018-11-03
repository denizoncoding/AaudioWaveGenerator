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

package com.denizoncoding.aaudiowavegenerator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener, SeekBar.OnSeekBarChangeListener {
    static {
        System.loadLibrary("native-lib");
    }

    public native void SetWaveType(int waveType_);

    public native void SetFrequnecy(float freq);

    public native void SetVolume(float vol);

    public native void SetTone(boolean on);

    public native int CreateEngine(float freq, float vol);

    public native int StartEngine();

    public native int PauseEngine();

    public native int StopEngine();

    public native void FlushStream();

    enum WaveType {
        Sine,
        Square,
        Sawtooth,
        Triangular
    }

    Switch toneSwitch;
    SeekBar frequencySeekBar;
    SeekBar volumeSeekBar;
    TextView frequencyTextView;
    TextView volumeTextView;
    RadioButton sineRadioButton, squareRadioButton, sawtoothRadioButton, triangularRadioButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        DefineWidgetsAndAddListeners();
        CreateEngine((frequencySeekBar.getProgress() * 20) / 880.0f,
                volumeSeekBar.getProgress() / 100.f);
    }
    @Override
    protected void onResume() {
        super.onResume();
        StartEngine();
    }

    @Override
    protected void onPause() {
        PauseEngine();
        super.onPause();
    }

    @Override
    protected void onStop() {
        StopEngine();
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        FlushStream();
        super.onDestroy();
    }

    private void DefineWidgetsAndAddListeners() {
        toneSwitch = findViewById(R.id.switchTone);
        frequencySeekBar = findViewById(R.id.seekBarFrequency);
        volumeSeekBar = findViewById(R.id.seekBarVolume);
        frequencyTextView = findViewById(R.id.textViewFrequency);
        volumeTextView = findViewById(R.id.textViewVolume);

        sineRadioButton = findViewById(R.id.radioButtonSine);
        squareRadioButton = findViewById(R.id.radioButtonSquare);
        sawtoothRadioButton = findViewById(R.id.radioButtonSawtooth);
        triangularRadioButton = findViewById(R.id.radioButtonTriangular);

        toneSwitch.setOnCheckedChangeListener(this);
        frequencySeekBar.setOnSeekBarChangeListener(this);
        volumeSeekBar.setOnSeekBarChangeListener(this);

        sineRadioButton.setOnCheckedChangeListener(this);
        squareRadioButton.setOnCheckedChangeListener(this);
        sawtoothRadioButton.setOnCheckedChangeListener(this);
        triangularRadioButton.setOnCheckedChangeListener(this);
    }

    private void SetToneFrequency(int prog) {
        float frequency = prog*2.0f;
        SetFrequnecy(frequency);
        SetFrequencyText(frequency + "Hz");
    }

    private void SetToneVolume(int prog) {
        float volume = (float) Math.log10((prog / 100.0f) + 1);
        SetVolume(volume);
        SetVolumeText(prog + "");
    }

    private void SetFrequencyText(String frequency) {
        frequencyTextView.setText("Frequency: " + frequency);
    }

    private void SetVolumeText(String rate) {
        volumeTextView.setText("Volume(%): " + rate);
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        switch (buttonView.getId()) {
            case R.id.switchTone:
                SetTone(isChecked);
                break;
            case R.id.radioButtonSine:
                if(sineRadioButton.isChecked()) {
                    SetWaveType(WaveType.Sine.ordinal());
                }
                break;
            case R.id.radioButtonSquare:
                if(squareRadioButton.isChecked()) {
                    SetWaveType(WaveType.Square.ordinal());
                }
                break;
            case R.id.radioButtonSawtooth:
                if(sawtoothRadioButton.isChecked()) {
                    SetWaveType(WaveType.Sawtooth.ordinal());
                }
                break;
            case R.id.radioButtonTriangular:
                if(triangularRadioButton.isChecked()) {
                    SetWaveType(WaveType.Triangular.ordinal());
                }
                break;
        }
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        switch (seekBar.getId()) {
            case R.id.seekBarFrequency:
                SetToneFrequency((progress+1));
                break;
            case R.id.seekBarVolume:
                SetToneVolume(progress);
                break;
        }
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {
// not using
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {
// not using
    }

}
