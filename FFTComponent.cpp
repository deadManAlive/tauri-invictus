#include "FFTComponent.h"

FFTSpectrum::FFTSpectrum(AudioPluginAudioProcessor& p)
    : processorRef(p) {
         /*TODO*/
        startTimer(15);
    }

FFTSpectrum::~FFTSpectrum() {}

void FFTSpectrum::paint(juce::Graphics& g) {
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello from frequency domain!", getLocalBounds(), juce::Justification::centred, 1);
}

void FFTSpectrum::resized() { /*TODO*/ }

void FFTSpectrum::timerCallback() { /*TODO*/ }