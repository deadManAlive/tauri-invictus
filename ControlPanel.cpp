#include "ControlPanel.h"

ControlPanel::ControlPanel(AudioPluginAudioProcessor& p)
    : processorRef(p) {}

ControlPanel::~ControlPanel() {}

void ControlPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::white);
    g.setColour (juce::Colours::red);
    g.setFont (15.0f);
    g.drawFittedText ("Hello, World!!", getLocalBounds(), juce::Justification::centred, 1);
}

void ControlPanel::resized() {}