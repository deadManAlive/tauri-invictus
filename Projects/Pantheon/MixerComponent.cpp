#include "MixerComponent.h"

MixerComponent::MixerComponent(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts)
    , rightToLeftGainSlider(Slider::LinearVertical, Slider::NoTextBox)
    , leftPreGainSlider(Slider::LinearVertical, Slider::NoTextBox)
    , rightPreGainSlider(Slider::LinearVertical, Slider::NoTextBox)
    , leftToRightGainSlider(Slider::LinearVertical, Slider::NoTextBox)
    , leftPanLook(PanLook::Origin::FromMid, PanLook::Channel::Left)
    , rightPanLook(PanLook::Origin::FromMid, PanLook::Channel::Right)
{
    addAndMakeVisible(rightToLeftGainSlider);
    rightToLeftGainSlider.setLookAndFeel(&rightPanLook);
    rightToLeftGainAttachment.reset(new SliderAttachment(parameters, "rightToLeftGain", rightToLeftGainSlider));

    addAndMakeVisible(leftPreGainSlider);
    leftPreGainSlider.setLookAndFeel(&leftPanLook);
    leftPreGainAttachment.reset(new SliderAttachment(parameters, "leftPreGain", leftPreGainSlider));

    addAndMakeVisible(rightPreGainSlider);
    rightPreGainSlider.setLookAndFeel(&rightPanLook);
    rightPreGainAttachment.reset(new SliderAttachment(parameters, "rightPreGain", rightPreGainSlider));

    addAndMakeVisible(leftToRightGainSlider);
    leftToRightGainSlider.setLookAndFeel(&leftPanLook);
    leftToRightGainAttachment.reset(new SliderAttachment(parameters, "leftToRightGain", leftToRightGainSlider));
}

MixerComponent::~MixerComponent() {}

void MixerComponent::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    const auto bounds = getLocalBounds().toFloat();
    const float width = bounds.getWidth();
    const float height = bounds.getHeight();

    const auto onepos = rightToLeftGainSlider.getPositionOfValue(1.0f);
    const auto negonepos = rightToLeftGainSlider.getPositionOfValue(-1.0f);


    g.setColour (Colours::mintcream);
    juce::Line<float> ones (juce::Point<float> (width / 4, onepos),
                            juce::Point<float> (3 * width / 4, onepos));
    juce::Line<float> zeros (juce::Point<float> (width / 4, height / 2),
                            juce::Point<float> (3 * width / 4, height / 2));
    juce::Line<float> negones (juce::Point<float> (width / 4, negonepos),
                            juce::Point<float> (3 * width / 4, negonepos));

    g.drawLine (zeros, 2.0f);
    g.drawLine(ones, 2.0f);
    g.drawLine(negones, 2.0f);
}

void MixerComponent::resized() {
    Grid grid;

    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    grid.templateRows = {
        Track(Fr(1))
    };
    grid.templateColumns = {
        Track(Fr(2)),
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(2))
    };

    grid.items = {
        GridItem(),
        GridItem(rightToLeftGainSlider),
        GridItem(leftPreGainSlider),
        GridItem(rightPreGainSlider),
        GridItem(leftToRightGainSlider),
        GridItem()
    };

    grid.performLayout(getLocalBounds());
}
