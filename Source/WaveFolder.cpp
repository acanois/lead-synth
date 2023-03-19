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

juce::AudioBuffer<float> WaveFolder::process_block(juce::AudioBuffer<float>& buffer) {
    auto outputBuffer = juce::AudioBuffer<float>();
    outputBuffer.setSize(1, buffer.getNumSamples());
    
    for (auto i = 0; i < buffer.getNumSamples(); ++i) {
        auto current = buffer.getWritePointer(0, i);
        auto foldedSample = processSample(*current);
        outputBuffer.addSample(0, i, foldedSample);
    }
    
    return outputBuffer;
}

float WaveFolder::processSample(float sample) {
    auto nyquist = mSpec.sampleRate / 2;
    auto tan_sum = (tanh(sample) * 2.f) * 0.9f;
    auto sineSample = sample * sin((2.f * juce::MathConstants<double>::pi) *
                                     (nyquist / mSpec.sampleRate));
    return tan_sum + sineSample;
}
