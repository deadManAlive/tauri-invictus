#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p)
    , processorRef(p)
    , parameters(apvts)
    , inputGainSlider(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow)
    , inputPanSlider(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow)
    , tooltipWindow(this)
{
    inputGainSlider.setTooltip("Input Gain");
    addAndMakeVisible(inputGainSlider);
    inputGainAttachment.reset(new SliderAttachment(parameters, "inputGain", inputGainSlider));

    inputPanSlider.setTooltip("Input Pan");
    addAndMakeVisible(inputPanSlider);
    inputPanAttachment.reset(new SliderAttachment(parameters, "inputPan", inputPanSlider));

    setResizable(false, false);
    setSize(420, 620);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}


//TODO: use grid / flexbox
void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::column;
    fb.flexWrap = FlexBox::Wrap::noWrap;

    fb.items.add(FlexItem(inputGainSlider).withMinHeight(120.f));
    fb.items.add(FlexItem(inputPanSlider).withMinHeight(120.f));

    fb.performLayout(getLocalBounds());
}