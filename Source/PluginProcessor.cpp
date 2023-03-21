/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeadSynthAudioProcessor::LeadSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

LeadSynthAudioProcessor::~LeadSynthAudioProcessor() {
}

//==============================================================================
const juce::String LeadSynthAudioProcessor::getName() const {
    return JucePlugin_Name;
}

bool LeadSynthAudioProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LeadSynthAudioProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LeadSynthAudioProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LeadSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int LeadSynthAudioProcessor::getNumPrograms() {
    /** Boilerplate: kept because I'll forget */
    // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
    return 1;
}

int LeadSynthAudioProcessor::getCurrentProgram() {
    return 0;
}

void LeadSynthAudioProcessor::setCurrentProgram (int index) {
}

const juce::String LeadSynthAudioProcessor::getProgramName (int index) {
    return {};
}

void LeadSynthAudioProcessor::changeProgramName (int index, const juce::String& newName) {
}

//==============================================================================
void LeadSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    mpVoice->prepareSpec(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
}

void LeadSynthAudioProcessor::releaseResources() {

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LeadSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LeadSynthAudioProcessor::processBlock(
   juce::AudioBuffer<float>& buffer,
   juce::MidiBuffer& midiMessages
) {
    juce::ScopedNoDenormals noDenormals;
    
    mpVoice->setFrequency(110.f);
    mpVoice->setLevel(0.5f);
    mpVoice->renderNextBlock(buffer, 0, buffer.getNumSamples());
}

//==============================================================================
bool LeadSynthAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessorEditor* LeadSynthAudioProcessor::createEditor() {
    return new LeadSynthAudioProcessorEditor (*this);
}

//==============================================================================
void LeadSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {

}

void LeadSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
 
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new LeadSynthAudioProcessor();
}
