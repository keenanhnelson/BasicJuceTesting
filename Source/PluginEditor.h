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
class BasicJuceTestingAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    BasicJuceTestingAudioProcessorEditor (BasicJuceTestingAudioProcessor&);
    ~BasicJuceTestingAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback();
    void handlePlaybackDetection();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicJuceTestingAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicJuceTestingAudioProcessorEditor)
};
