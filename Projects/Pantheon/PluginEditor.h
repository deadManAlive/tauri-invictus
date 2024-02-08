#pragma once

#include "PluginProcessor.h"
#include <memory>

// #include <memory>
// #include "BinaryData.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    AudioProcessorValueTreeState& parameters;

    juce::Slider inputGainSlider;
    std::unique_ptr<SliderAttachment> inputGainAttachment;

    juce::Slider inputPanSlider;
    std::unique_ptr<SliderAttachment> inputPanAttachment;

    TooltipWindow tooltipWindow;

    // juce::Image backGroundImg = juce::ImageCache::getFromMemory(BinaryData::bgscribble_png, BinaryData::bgscribble_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};