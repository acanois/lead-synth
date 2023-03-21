/*
  ==============================================================================

    LeadVoice.h
    Created: 12 Mar 2023 12:19:03pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "WaveFolder.h"

class LeadVoice : public juce::SynthesiserVoice {
public:
    LeadVoice();
    
    bool canPlaySound (juce::SynthesiserSound* synthSound) override;
    
    void startNote (int midiNoteNumber,
                    float velocity,
                    juce::SynthesiserSound *sound,
                    int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void prepareVoice (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer,
                          int startSample,
                          int numSamples) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void setFrequency (float newValue, bool force = false);
    void setLevel (float newValue);
    
    void prepareSpec (double sampleRate, int samplesPerBlock, int numOutputChannels);
    
private:
    enum {
        oscillator,
        waveShaper,
        gain,
    };
    
    juce::dsp::ProcessSpec mSpec;
    juce::dsp::ProcessorChain<
        juce::dsp::Oscillator<float>,
        juce::dsp::WaveShaper<float>,
        juce::dsp::Gain<float>
    > mProcessorChain;
    
//    std::unique_ptr<WaveFolder> mFolder;
};
