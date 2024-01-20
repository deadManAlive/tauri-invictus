#include <JuceHeader.h>

#include "PluginProcessor.h"

class FFTSpectrum : public juce::Component, public juce::Timer
{
public:
    FFTSpectrum(AudioPluginAudioProcessor& p);
    ~FFTSpectrum();
    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
private:
    AudioPluginAudioProcessor& processorRef;

    int counter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTSpectrum)
};