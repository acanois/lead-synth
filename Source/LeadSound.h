/*
  ==============================================================================

    LeadSound.h
    Created: 12 Mar 2023 12:18:53pm
    Author:  David Richter

  ==============================================================================
*/

#pragma once

class LeadSound  : public SynthesiserSound {
    bool appliesToNote (int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
