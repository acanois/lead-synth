/*
  ==============================================================================

    WaveFolder.cpp
    Created: 19 Mar 2023 11:51:23am
    Author:  David Richter

  ==============================================================================
*/

#include "WaveFolder.h"

using juce::dsp::FastMathApproximations;

WaveFolder::WaveFolder(const juce::dsp::ProcessSpec& spec)
    : mSpec(spec)
{ }

juce::AudioBuffer<float> WaveFolder::processBlock(juce::AudioBuffer<float>& buffer) {
//    for (auto i = 0; i < buffer.getNumSamples(); ++i) {
//        auto current = buffer.getWritePointer(0, i);
//        *current = processSample(*current);
//    }
//
//    return buffer;
    auto outputBuffer = juce::AudioBuffer<float>();
    outputBuffer.setSize(1, buffer.getNumSamples());

    for (auto i = 0; i < buffer.getNumSamples(); ++i) {
        auto current = buffer.getReadPointer(0, i);
        DBG(*current);
        auto foldedSample = processSample(*current);
        outputBuffer.setSample(0, i, foldedSample);
    }
    
    return outputBuffer;
}

float WaveFolder::processSample(float sample) {
//    auto nyquist = mSpec.sampleRate / 2;
//    auto tan_sum = (tanh(sample) * 2.f) * 0.9f;
//
//    return tan_sum + sample;
    return sample;
}

juce::AudioBuffer<float> WaveFolder::passThru(juce::AudioBuffer<float>& buffer) {
    DBG(*buffer.getReadPointer(0));
    return buffer;
}
