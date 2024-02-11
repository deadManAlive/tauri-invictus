#pragma once

#include "juce_core/system/juce_PlatformDefs.h"
#include <JuceHeader.h>

//==============================================================================
class PantheonProcessorBase  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PantheonProcessorBase()
        : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo())
                                           .withOutput ("Output", juce::AudioChannelSet::stereo()))
    {}
    //==============================================================================
    void prepareToPlay (double, int) override {}
    void releaseResources() override {}
    void processBlock (juce::AudioSampleBuffer&, juce::MidiBuffer&) override {}

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override          { return nullptr; }
    bool hasEditor() const override                              { return false; }

    //==============================================================================
    const juce::String getName() const override                  { return {}; }
    bool acceptsMidi() const override                            { return false; }
    bool producesMidi() const override                           { return false; }
    double getTailLengthSeconds() const override                 { return 0; }

    //==============================================================================
    int getNumPrograms() override                                { return 0; }
    int getCurrentProgram() override                             { return 0; }
    void setCurrentProgram (int) override                        {}
    const juce::String getProgramName (int) override             { return {}; }
    void changeProgramName (int, const juce::String&) override   {}

    //==============================================================================
    void getStateInformation (juce::MemoryBlock&) override       {}
    void setStateInformation (const void*, int) override         {}

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PantheonProcessorBase)
};

namespace process {
    //==============================================================================
    class PreProcessor : public PantheonProcessorBase {
    public:
        PreProcessor(AudioProcessorValueTreeState&);
        void prepareToPlay(double, int) override;
        void processBlock(AudioSampleBuffer&, MidiBuffer&) override;
        void reset() override;
        const String getName() const override {return "Pre";}
    private:
        //==============================================================================
        AudioProcessorValueTreeState& parameters;
        dsp::ProcessorChain<dsp::Gain<float>, dsp::Panner<float>> preProcessorChain;
        void updateParameter();

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreProcessor)
    };

    //==============================================================================
    enum class Channel {
        Left,
        Right,
    };

    //==============================================================================
    template<Channel C>
    class PostProcessor : public PantheonProcessorBase {
    public:
        PostProcessor(AudioProcessorValueTreeState& apvts)
            : parameters(apvts)
        {
        }

        void prepareToPlay(double sampleRate, int samplesPerBlock) override {
            panner.setRule(juce::dsp::PannerRule::balanced);
            panner.prepare(
            {sampleRate, (uint32)samplesPerBlock, 2}
            );
        }
        
        void processBlock(AudioSampleBuffer& buffer, MidiBuffer&) override {
            updateParameter();

            dsp::AudioBlock<float>block(buffer);
            dsp::ProcessContextReplacing<float>context(block);

            panner.process(context);
        }

        void reset() override {
            panner.reset();
        }
        
        const String getName() const override {
            return "Post";
        }
    private:
        //==============================================================================
        AudioProcessorValueTreeState& parameters;
        dsp::Panner<float> panner;
        
        //==============================================================================
        static constexpr auto z = C == Channel::Left ? "leftPan" : "rightPan";

        //==============================================================================
        void updateParameter() {
            const auto panValue = parameters.getRawParameterValue(z)->load();
            panner.setPan(panValue);
        }

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PostProcessor)
    };
}
