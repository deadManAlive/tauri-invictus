#include "ControlPanel.h"

ControlPanel::ControlPanel(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts)
    , skewSlider(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow)
{
    skewSlider.setSkewFactorFromMidPoint(0.036f);
    addAndMakeVisible(skewSlider);
    skewAttachment.reset(new SliderAttachment(parameters, "skew", skewSlider));
}

ControlPanel::~ControlPanel() {}

void ControlPanel::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void ControlPanel::resized() {
    auto r = getLocalBounds();
    skewSlider.setBounds(r);
}