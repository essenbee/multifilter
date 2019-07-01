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
					pluginState (*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
}

MultifilterAudioProcessor::~MultifilterAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout MultifilterAudioProcessor::createParameterLayout()
{
	std::vector<std::unique_ptr<RangedAudioParameter>> audioParams;

	auto cutoffFrequencyParam = std::make_unique<AudioParameterInt>("cutoff", "Cutoff Frequency", 20, 20480, 1000);
	auto qFactorParam = std::make_unique<AudioParameterFloat>("qfactor", "Q Factor", 0.707f, 20.0f, 0.707f);
	auto boostParam = std::make_unique<AudioParameterFloat>("boost", "Boost/Cut", -20.0f, 20.0f, 0.0f);
	auto filterTypeParam = std::make_unique<AudioParameterInt>("filter_type", "Filter Type", 0, 28, 0);

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

	leftAudioFilter.reset(sampleRate);
	rightAudioFilter.reset(sampleRate);
}

void MultifilterAudioProcessor::updateParameters()
{
	auto filterParameters = leftAudioFilter.getParameters();
	filterParameters.fc = *pluginState.getRawParameterValue("cutoff");
	filterParameters.Q = *pluginState.getRawParameterValue("qfactor");
	filterParameters.boostCut_dB = *pluginState.getRawParameterValue("boost");

	int filterType = *pluginState.getRawParameterValue("filter_type");

	filterParameters.algorithm = static_cast<filterAlgorithm>(filterType);

	leftAudioFilter.setParameters(filterParameters);
	rightAudioFilter.setParameters(filterParameters);
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

	updateParameters();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

		auto* inputDataLeft = buffer.getReadPointer(0);
        auto* outputDataLeft = buffer.getWritePointer(0);
		auto* inputDataRight = buffer.getReadPointer(1);
		auto* outputDataRight = buffer.getWritePointer(1);

		for (int i = 0; i < buffer.getNumSamples(); i++)
		{
			float inputSampleLeft = inputDataLeft[i];
			float inputSampleRight = inputDataRight[i];

			outputDataLeft[i] = leftAudioFilter.processAudioSample(inputSampleLeft);
			outputDataRight[i] = rightAudioFilter.processAudioSample(inputSampleRight);
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
