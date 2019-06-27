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
    setSize (800, 300);

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

	filterTypeControl.addItemList(
		{ "LPF1P", "LPF1", "HPF1", "LPF2", "HPF2", "BPF2", "BSF2", "ButterLPF2", "ButterHPF2",
		  "ButterBPF2", "ButterSF2", "MMALPF2", "MMALPF2B", "LowShelf", "HighShelf", "NCQParaEQ",
		  "CQParaEQ", "LWRLPF2", "LWRHPF2", "APF1", "APF2", "ResonA", "ResonB", "MatchLP2A",
		  "MatchLP2B", "MatchBP2A", "MatchBF2B", "ImpInvLP1", "ImpInvLP2" }, 1);
	filterTypeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.pluginState, "filter_type", filterTypeControl);
	filterTypeControl.setText("Filter Type");
	
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
	cutoffFreqControl.setBoundsRelative(0.05f, 0.1f, 0.1f, 0.1f);
	qFactorControl.setBoundsRelative(0.15f, 0.1f, 0.1f, 0.1f);
	boostControl.setBoundsRelative(0.25f, 0.1f, 0.1f, 0.1f);
	filterTypeControl.setBoundsRelative(0.35f, 0.1f, 0.25f, 0.05f);
}
