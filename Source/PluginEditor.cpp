/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeadSynthAudioProcessorEditor::LeadSynthAudioProcessorEditor(LeadSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      mKeyboardComponent(mKeyBoardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(mKeyboardComponent);
    
    // Has to be set last
    setSize (1280, 720);
}

LeadSynthAudioProcessorEditor::~LeadSynthAudioProcessorEditor() {
}

//==============================================================================
void LeadSynthAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void LeadSynthAudioProcessorEditor::resized() {
    auto area = getLocalBounds();
    
    juce::Rectangle<int> componentBounds;
    componentBounds.setBounds(100, 100, 100, 100);
    mKeyboardComponent.setBounds(area.removeFromBottom(80).reduced(8));
}
