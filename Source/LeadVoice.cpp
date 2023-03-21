/*
  ==============================================================================

    LeadVoice.cpp
    Created: 12 Mar 2023 12:25:02pm
    Author:  David Richter

  ==============================================================================
*/

#include "LeadVoice.h"

LeadVoice::LeadVoice() {
    auto& osc = mProcessorChain.template get<oscillator>();
    auto& shaper = mProcessorChain.template get<waveShaper>();
    
    osc.initialise ([] (float x) { return std::sin (x); }, 128);
    shaper.functionToUse = [] (float x) {
        return tanh(x) + sin(x * (2.f * juce::MathConstants<float>::pi));
    };
}

bool LeadVoice::canPlaySound(juce::SynthesiserSound* leadSound) {
    return dynamic_cast<LeadVoice*> (leadSound) != nullptr;
}

void LeadVoice::startNote (
    int midiNoteNumber,
    float velocity,
    juce::SynthesiserSound *sound,
    int currentPitchWheelPosition
) {
    DBG(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    setFrequency(midiNoteNumber);
}

void LeadVoice::stopNote(float velocity, bool allowTailOff) {

}

void LeadVoice::prepareVoice(double sampleRate, int samplesPerBlock, int numOutputChannels) {

}

void LeadVoice::prepareSpec(double sampleRate, int samplesPerBlock, int numOutputChannels) {
    mSpec.sampleRate = sampleRate;
    mSpec.maximumBlockSize = samplesPerBlock;
    mSpec.numChannels = numOutputChannels;
    mProcessorChain.prepare(mSpec);
    
//    mFolder = std::make_unique<WaveFolder>(mSpec);
}

void LeadVoice::renderNextBlock(
    juce::AudioBuffer<float>& outputBuffer,
    int startSample,
    int numSamples
) {
    auto block = juce::dsp::AudioBlock<float>(outputBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    mProcessorChain.process(context);
}

void LeadVoice::pitchWheelMoved(int newPitchWheelValue) {
    
}

void LeadVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    
}

void LeadVoice::setFrequency(float newValue, bool force)  {
    auto& osc = mProcessorChain.template get<oscillator>();
    osc.setFrequency (newValue, force);
}

void LeadVoice::setLevel(float newValue) {
    auto& gainLevel = mProcessorChain.template get<gain>();
    gainLevel.setGainLinear (newValue);
}
