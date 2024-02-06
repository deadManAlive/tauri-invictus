#pragma once

#include "PluginProcessor.h"
#include <memory>
// #include "BinaryData.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         private juce::Slider::Listener,
                                         private juce::Timer
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

    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    juce::Slider lPreGainSlider;
    juce::Slider rPreGainSlider;
    juce::Slider l2rGainSlider;
    juce::Slider r2lGainSlider;
    juce::Slider leftPanSlider;
    juce::Slider rightPanSlider;

    juce::Slider mainGainSlider;
    std::unique_ptr<SliderAttachment> mainGainAttachment;

    // juce::Image backGroundImg = juce::ImageCache::getFromMemory(BinaryData::bgscribble_png, BinaryData::bgscribble_pngSize);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};