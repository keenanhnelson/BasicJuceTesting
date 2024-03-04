/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DataTransferAudioProcessorEditor::DataTransferAudioProcessorEditor (DataTransferAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    startTimer(500);
}

DataTransferAudioProcessorEditor::~DataTransferAudioProcessorEditor()
{
}

//==============================================================================
void DataTransferAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    int lineHeight = 10; // Adjust line height as needed
    int yPosition = 10; // Start position from the top
    int xPosition = 10; // Start position from the left

    int scopeSize = audioProcessor.getScopeDataSize();
    const float* scopeData = audioProcessor.getScopeData();

    for (int i = 0; i < 20; ++i)
    {
        // Convert each float value to a string
        auto valueString = std::to_string(scopeData[i]); // Change '4' to the desired number of decimal places

        // Draw the string at appropriate positions
        g.drawText(valueString, xPosition, yPosition + i * lineHeight, getWidth(), lineHeight, juce::Justification::left);
    }
}

void DataTransferAudioProcessorEditor::resized()
{

}

void DataTransferAudioProcessorEditor::timerCallback() {
    handlePlaybackDetection();
}

void DataTransferAudioProcessorEditor::handlePlaybackDetection() {
    if (audioProcessor.processBlockPreviouslyCalled) {
        if (audioProcessor.processBlockCalled) {
            //Is currently playing
            audioProcessor.processBlockPreviouslyCalled = true;
            audioProcessor.processBlockCalled = false;//Reset to false. Should be set to true by processBlock if play is still happening
        }
        else {
            //Play has stopped
            audioProcessor.processBlockPreviouslyCalled = false;
            audioProcessor.processingAudio = false;
            repaint();//This should paint the new values to the screen
        }
    }
    else {
        if (audioProcessor.processBlockCalled) {
            //Play just started
            audioProcessor.processBlockPreviouslyCalled = true;
            audioProcessor.processBlockCalled = false;//Reset to false. Should be set to true by processBlock if play is still happening
        }
    }
}