#include <JuceHeader.h>

#include "PluginProcessor.h"

class ControlPanel : public juce::Component
{
public:
    ControlPanel(AudioPluginAudioProcessor& p);
    ~ControlPanel();
    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanel)
};