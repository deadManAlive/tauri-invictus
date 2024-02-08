#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p)
    , processorRef(p)
    , parameters(apvts)
    , inputGainSlider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
    , inputPanSlider(Slider::RotaryHorizontalVerticalDrag, Slider::NoTextBox)
    , mixerComponent(p, apvts)
    , tooltipWindow(this)
{
    inputGainSlider.setTooltip("Input Gain");
    addAndMakeVisible(inputGainSlider);
    inputGainAttachment.reset(new SliderAttachment(parameters, "inputGain", inputGainSlider));

    inputPanSlider.setTooltip("Input Pan");
    addAndMakeVisible(inputPanSlider);
    inputPanAttachment.reset(new SliderAttachment(parameters, "inputPan", inputPanSlider));

    addAndMakeVisible(mixerComponent);

    double ratio = 2./3.;
    int min_height = 200;
    int max_height = 1080;
    int default_size = 420;
    setResizeLimits(min_height, (int)(min_height/ratio), max_height, (int)(max_height/ratio));
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(default_size, (int)(default_size/ratio));
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


void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // FlexBox fb;
    // fb.flexDirection = FlexBox::Direction::column;
    // fb.flexWrap = FlexBox::Wrap::noWrap;

    // fb.items.add(FlexItem(inputGainSlider).withMinHeight(120.f));
    // fb.items.add(FlexItem(inputPanSlider).withMinHeight(120.f));
    // fb.items.add(FlexItem(mixerComponent).withMinHeight(120.f));

    // fb.performLayout(getLocalBounds());

    Grid grid;

    using Track = Grid::TrackInfo;
    using Fr = Grid::Fr;

    grid.templateRows = {
        Track(Fr(1)),
        Track(Fr(1)),
        Track(Fr(3)),
        Track(Fr(1))
    };
    grid.templateColumns = {Track(Fr(1))};

    grid.items = {
        GridItem(inputGainSlider),
        GridItem(inputPanSlider),
        GridItem(mixerComponent)
    };

    grid.performLayout(getLocalBounds());
}