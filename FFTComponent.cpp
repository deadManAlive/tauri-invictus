#include "FFTComponent.h"

FFTSpectrum::FFTSpectrum(AudioPluginAudioProcessor& p)
    : processorRef(p)
    , counter{0} 
{
        /*TODO*/
    startTimerHz(1);
}

FFTSpectrum::~FFTSpectrum() {}

void FFTSpectrum::paint(juce::Graphics& g) {
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);

    const auto bounds = getBounds();
    const auto topLeft = bounds.getTopLeft();
    const auto str = juce::String::formatted("TL: %d %d %d", topLeft.getX(), topLeft.getY(), counter);

    g.drawFittedText (str, getLocalBounds(), juce::Justification::centred, 1);
}

void FFTSpectrum::resized() { /*TODO*/ }

void FFTSpectrum::timerCallback() { 
    counter += 1;
    repaint();
 }