/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DataTransferAudioProcessor::DataTransferAudioProcessor()
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
    id = instances;
    instances++;
}

DataTransferAudioProcessor::~DataTransferAudioProcessor()
{
}

//==============================================================================
const juce::String DataTransferAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DataTransferAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DataTransferAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DataTransferAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DataTransferAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DataTransferAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DataTransferAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DataTransferAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DataTransferAudioProcessor::getProgramName (int index)
{
    return {};
}

void DataTransferAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DataTransferAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DataTransferAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DataTransferAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DataTransferAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto* channelData = buffer.getReadPointer(0);

    for (int i = 0; i < 20; i++) {
        scopeData[i] = channelData[i];
    }

    volatile int a = 0;
    a++;
    a++;
}

//==============================================================================
bool DataTransferAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DataTransferAudioProcessor::createEditor()
{
    auto a = new DataTransferAudioProcessorEditor(*this);
    return a;
}

//==============================================================================
void DataTransferAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DataTransferAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DataTransferAudioProcessor();
}

const float* DataTransferAudioProcessor::getScopeData() {
    return scopeData;
}

int DataTransferAudioProcessor::getScopeDataSize() {
    return scopeDataSize;
}

int DataTransferAudioProcessor::instances = 0;
float DataTransferAudioProcessor::scopeData[scopeDataSize] = { 0 };