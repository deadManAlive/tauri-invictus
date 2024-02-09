#include "PreComponent.h"

PreComponent::PreComponent(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts)
    , inputGainSlider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
    , inputPanSlider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
    , panLok(PanLook::Type::Pan)
    , volLok(PanLook::Type::Gain)
{
    inputGainSlider.setTooltip("Input Gain");
    inputGainSlider.setLookAndFeel(&volLok);
    addAndMakeVisible(inputGainSlider);
    inputGainAttachment.reset(new SliderAttachment(parameters, "inputGain", inputGainSlider));

    inputPanSlider.setTooltip("Input Pan");
    inputPanSlider.setLookAndFeel(&panLok);
    addAndMakeVisible(inputPanSlider);
    inputPanAttachment.reset(new SliderAttachment(parameters, "inputPan", inputPanSlider));
}

PreComponent::~PreComponent() {}

void PreComponent::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void PreComponent::resized() {
    Grid grid;

    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
    };
    grid.templateColumns = {Track(Fr(1))};

    grid.items = {
        GridItem(inputGainSlider),
        GridItem(inputPanSlider),
    };

    grid.performLayout(getLocalBounds());
}
