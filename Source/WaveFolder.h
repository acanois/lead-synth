/*
  ==============================================================================

    WaveFolder.h
    Created: 19 Mar 2023 11:51:23am
    Author:  David Richter

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class WaveFolder {
public:
    WaveFolder(const juce::dsp::ProcessSpec& spec);
    
    juce::AudioBuffer<float> processBlock(juce::AudioBuffer<float>& buffer);
    juce::AudioBuffer<float> passThru(juce::AudioBuffer<float>& buffer);
    
private:
    float processSample(float sample);
    
private:
    const juce::dsp::ProcessSpec mSpec;
};
