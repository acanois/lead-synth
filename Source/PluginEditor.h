/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LeadSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LeadSynthAudioProcessorEditor (LeadSynthAudioProcessor&);
    ~LeadSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    LeadSynthAudioProcessor& audioProcessor;
    
    // Keyboard
    juce::MidiKeyboardState mKeyBoardState;
    juce::MidiKeyboardComponent mKeyboardComponent;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeadSynthAudioProcessorEditor)
};
