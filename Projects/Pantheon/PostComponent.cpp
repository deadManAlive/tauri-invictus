#include "PostComponent.h"

PostComponent::PostComponent(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts)
    , leftPostPanSlider(Slider::LinearHorizontal, Slider::NoTextBox)
    , rightPostPanSlider(Slider::LinearHorizontal, Slider::NoTextBox)
{
    addAndMakeVisible(leftPostPanSlider);
    leftPostPanAttachment.reset(new SliderAttachment(parameters, "leftPan", leftPostPanSlider));

    addAndMakeVisible(rightPostPanSlider);
    rightPostPanAttachment.reset(new SliderAttachment(parameters, "rightPan", rightPostPanSlider));
}

PostComponent::~PostComponent() {}

void PostComponent::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PostComponent::resized() {
    Grid grid;

    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
    };
    grid.templateColumns = {Track(Fr(1))};

    grid.items = {
        GridItem(leftPostPanSlider),
        GridItem(rightPostPanSlider),
    };

    grid.performLayout(getLocalBounds());
}
