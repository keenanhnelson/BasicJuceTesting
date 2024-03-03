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