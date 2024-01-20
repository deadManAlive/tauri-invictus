#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
    , fftSpectrum (processorRef)
    , controlPanel (processorRef)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(fftSpectrum);
    addAndMakeVisible(controlPanel);

    double ratio = 16.0/9.0;
    int min_height = 400;
    int max_height = 1600;
    int default_size = 600;
    setResizeLimits(min_height, static_cast<int>(min_height/ratio), max_height, static_cast<int>(max_height/ratio));
    getConstrainer()->setFixedAspectRatio(ratio);
    setSize(default_size, static_cast<int>(default_size/ratio));
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    // auto bounds = getLocalBounds();
    // fftSpectrum.setBounds(bounds);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    grid.templateRows = {Track(Fr(1))};
    grid.templateColumns = {Track(Fr(1)), Track(Fr(3))};

    grid.items = {
        juce::GridItem (controlPanel),
        juce::GridItem (fftSpectrum)
    };

    grid.performLayout (getLocalBounds());
}
