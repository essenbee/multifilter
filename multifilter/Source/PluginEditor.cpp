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
    setSize (500, 200);

	pluginName.setText("Codebase Alpha Multi-filter", dontSendNotification);
	addAndMakeVisible(&pluginName);

	makeRotorySlider(&cutoffFreqControl, " Cutoff Frequency (Hz)", this);
	cutoffFreqValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.pluginState, "cutoff", cutoffFreqControl);
	addAndMakeVisible(&cutoffFreqControl);

	makeRotorySlider(&qFactorControl, " Q", this);
	qFactorValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.pluginState, "qfactor", qFactorControl);
	addAndMakeVisible(&qFactorControl);

	makeRotorySlider(&boostControl, " Feedback (dB)", this);
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

void MultifilterAudioProcessorEditor::makeRotorySlider(Slider* slider, String suffix, Component* parent)
{
	slider->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	slider->setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	slider->setPopupDisplayEnabled(true, true, parent);
	slider->setTextValueSuffix(suffix);
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

	Grid grid;

	grid.templateRows = { Grid::TrackInfo(1_fr), Grid::TrackInfo(1_fr) };
	grid.templateColumns = { Grid::TrackInfo(1_fr), Grid::TrackInfo(1_fr), Grid::TrackInfo(1_fr), Grid::TrackInfo(2_fr) };

	grid.items = { 
		GridItem(pluginName)
		.withArea(GridItem::Property(1), GridItem::Property(1), GridItem::Property(1), GridItem::Property(5))
		.withJustifySelf(GridItem::JustifySelf::center),
		GridItem(cutoffFreqControl), 
		GridItem(qFactorControl), 
		GridItem(boostControl), 
		GridItem(filterTypeControl)
		    .withHeight(40)
		    .withWidth(150)
		    .withAlignSelf(GridItem::AlignSelf::center)
	        .withJustifySelf(GridItem::JustifySelf::center) };

	grid.performLayout(getLocalBounds());
}
