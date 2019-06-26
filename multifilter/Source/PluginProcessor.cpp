/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultifilterAudioProcessor::MultifilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
					pluginState(* this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
	filterTypes.add("FilterA");
	filterTypes.add("FilterB");
	filterTypes.add("FilterC");
	filterTypes.add("FilterD");
	filterTypes.add("FilterE");
	filterTypes.add("FilterF");
}

MultifilterAudioProcessor::~MultifilterAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout MultifilterAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<RangedAudioParameter>> audioParams;

	auto cutoffFrequencyParam = std::make_unique<AudioParameterInt>("cutoff", "Cutoff_Frequency", 20, 20480, 1000);
	auto qFactorParam = std::make_unique<AudioParameterFloat>("qfactor", "Q_Factor", 0.707f, 20.0f, 0.707f);
	auto boostParam = std::make_unique<AudioParameterFloat>("boost", "Boost", -20.0f, 20.0f, 0.0f);

    StringArray filterTypes;
	filterTypes.add("FilterA");
	filterTypes.add("FilterB");
	filterTypes.add("FilterC");
	filterTypes.add("FilterD");
	filterTypes.add("FilterE");
	filterTypes.add("FilterF");

	auto filterTypeParam = std::make_unique<AudioParameterChoice>("filter_type", "Filter_Type", filterTypes, 1);

	audioParams.push_back(std::move(cutoffFrequencyParam));
	audioParams.push_back(std::move(qFactorParam));
	audioParams.push_back(std::move(boostParam));
	audioParams.push_back(std::move(filterTypeParam));

	return { audioParams.begin(), audioParams.end() };
}

//==============================================================================
const String MultifilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultifilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultifilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultifilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultifilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultifilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultifilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultifilterAudioProcessor::setCurrentProgram (int index)
{
}

const String MultifilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultifilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MultifilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MultifilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultifilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void MultifilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool MultifilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultifilterAudioProcessor::createEditor()
{
    return new MultifilterAudioProcessorEditor (*this);
}

//==============================================================================
void MultifilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultifilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultifilterAudioProcessor();
}
