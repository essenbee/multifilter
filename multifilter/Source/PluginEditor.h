/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MultifilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MultifilterAudioProcessorEditor (MultifilterAudioProcessor&);
    ~MultifilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultifilterAudioProcessor& processor;
	Slider cutoffFreqControl;
	Slider qFactorControl;
	Slider boostControl;
	ComboBox filterTypeControl;
	Label pluginName;

	void makeRotorySlider(Slider* slider, String suffix, Component* parent);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultifilterAudioProcessorEditor)

public:
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffFreqValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> qFactorValue;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> boostValue;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeValue;
};
