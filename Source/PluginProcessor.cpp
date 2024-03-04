/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BasicJuceTestingAudioProcessor::BasicJuceTestingAudioProcessor()
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

BasicJuceTestingAudioProcessor::~BasicJuceTestingAudioProcessor()
{
}

//==============================================================================
const juce::String BasicJuceTestingAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BasicJuceTestingAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BasicJuceTestingAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BasicJuceTestingAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BasicJuceTestingAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BasicJuceTestingAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BasicJuceTestingAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BasicJuceTestingAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BasicJuceTestingAudioProcessor::getProgramName (int index)
{
    return {};
}

void BasicJuceTestingAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BasicJuceTestingAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BasicJuceTestingAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BasicJuceTestingAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void BasicJuceTestingAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    processBlockCalled = true;
    auto* channelData = buffer.getReadPointer(0);

    for (int i = 0; i < buffer.getNumSamples() && scopeDataIndex < scopeDataSize; i++, scopeDataIndex++) {
        scopeData[scopeDataIndex] = channelData[i];
    }

    volatile int a = 0;
    a++;
    a++;
}

//==============================================================================
bool BasicJuceTestingAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BasicJuceTestingAudioProcessor::createEditor()
{
    auto a = new BasicJuceTestingAudioProcessorEditor(*this);
    return a;
}

//==============================================================================
void BasicJuceTestingAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BasicJuceTestingAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BasicJuceTestingAudioProcessor();
}

const float* BasicJuceTestingAudioProcessor::getScopeData() {
    return scopeData;
}

int BasicJuceTestingAudioProcessor::getScopeDataSize() {
    return scopeDataSize;
}

int BasicJuceTestingAudioProcessor::instances = 0;
float BasicJuceTestingAudioProcessor::scopeData[scopeDataSize] = { 0 };
int BasicJuceTestingAudioProcessor::scopeDataIndex = 0;
bool BasicJuceTestingAudioProcessor::processBlockCalled = false;
bool BasicJuceTestingAudioProcessor::processBlockPreviouslyCalled = false;
bool BasicJuceTestingAudioProcessor::processingAudio = false;