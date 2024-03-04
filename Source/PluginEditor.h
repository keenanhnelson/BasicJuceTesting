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
class DataTransferAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    DataTransferAudioProcessorEditor (DataTransferAudioProcessor&);
    ~DataTransferAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback();
    void handlePlaybackDetection();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DataTransferAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataTransferAudioProcessorEditor)
};
