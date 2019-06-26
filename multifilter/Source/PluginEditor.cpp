/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MultifilterAudioProcessorEditor::MultifilterAudioProcessorEditor (MultifilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1200, 300);

	cutoffFreqControl.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	cutoffFreqControl.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	cutoffFreqControl.setPopupDisplayEnabled(true, true, this);
	cutoffFreqControl.setTextValueSuffix(" Cutoff Frequency");
	cutoffFreqValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.pluginState, "cutoff", cutoffFreqControl);

	addAndMakeVisible(&cutoffFreqControl);

	qFactorControl.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	qFactorControl.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	qFactorControl.setPopupDisplayEnabled(true, true, this);
	qFactorControl.setTextValueSuffix(" Q");
	qFactorValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.pluginState, "qfactor", qFactorControl);

	addAndMakeVisible(&qFactorControl);

	boostControl.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	boostControl.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	boostControl.setPopupDisplayEnabled(true, true, this);
	boostControl.setTextValueSuffix(" dB");
	boostValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.pluginState, "boost", boostControl);

	addAndMakeVisible(&boostControl);

	filterTypeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.pluginState, "filter_type", filterTypeControl);

	addAndMakeVisible(&filterTypeControl);
}

MultifilterAudioProcessorEditor::~MultifilterAudioProcessorEditor()
{
}

//==============================================================================
void MultifilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MultifilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	cutoffFreqControl.setBoundsRelative(0.1f, 0.1f, 0.1f, 0.1f);
	qFactorControl.setBoundsRelative(0.2f, 0.1f, 0.1f, 0.1f);
	boostControl.setBoundsRelative(0.3f, 0.1f, 0.1f, 0.1f);
	filterTypeControl.setBoundsRelative(0.4f, 0.1f, 0.25f, 0.1f);
}
