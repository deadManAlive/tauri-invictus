#include "FFTComponent.h"
#include "PluginProcessor.h"
#include <cmath>

FFTSpectrum::FFTSpectrum(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts)
    , scopeData{}
{   
    startTimerHz(60);
}

FFTSpectrum::~FFTSpectrum() {}

void FFTSpectrum::paint(juce::Graphics& g) {
    TRACE_COMPONENT();

    g.fillAll(juce::Colours::black);
    g.setOpacity(1.0f);
    g.setColour(juce::Colours::white);

    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();

    for (int i = 1; i < (scopeSize - 1); ++i) {
        g.drawLine({
            (float) jmap(i, 0, scopeSize - 1, 0, width),
            (float) height,
            (float) jmap(i, 0, scopeSize - 1, 0, width),
            jmap (scopeData[(size_t) i], 0.0f, 1.0f, (float) height, 0.0f)
        });
    }
}

void FFTSpectrum::resized() { /*TODO*/ }

void FFTSpectrum::timerCallback() {
    if (processorRef.getBufferFreeSpace() == 0) {
        // TODO: current structure READ BY DEQUEUEING, hence discontinuous data across windows. WE DO NOT WANT that.
        processorRef.processFftData();

        const auto minDB = -90.f;
        const auto maxDB = 0.f;
        const auto analyzerMaxDB = 1.f;
        const auto levelFactor = 1.f / (pow(10.f, analyzerMaxDB / 20.f));

        auto skewValue = (parameters.getRawParameterValue("skew"));

        for (int i = 0; i < scopeSize; ++i) {
            auto skewedProportionX = 1.f - std::exp(std::log(1.f - (float) i / (float) scopeSize) * (*skewValue));
            auto fftDataIndex = juce::jlimit(0, (int)fftSize / 2, (int)(skewedProportionX * (float) fftSize * 0.5f));
            auto level = juce::jmap(
                juce::jlimit(
                    minDB, maxDB,
                    juce::Decibels::gainToDecibels(processorRef.getFftData(fftDataIndex)) - juce::Decibels::gainToDecibels((float) fftSize)
                ),
                minDB, maxDB, 0.f, levelFactor
            );

            scopeData[(size_t) i] = level;
        }

        repaint();
    }
}