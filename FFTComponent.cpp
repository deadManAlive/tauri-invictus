#include "FFTComponent.h"

FFTSpectrum::FFTSpectrum(AudioPluginAudioProcessor& p)
    : processorRef(p)
    , scopeData{}
{
    startTimerHz(60);
}

FFTSpectrum::~FFTSpectrum() {}

void FFTSpectrum::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
    g.setOpacity(1.0f);
    g.setColour(juce::Colours::white);

    for (int i = 1; i < (scopeSize - 1); ++i) {
        auto width = getLocalBounds().getWidth();
        auto height = getLocalBounds().getHeight();

        // TODO: doing this log in runtime is stupid
        g.drawLine({
            juce::mapFromLog10((float) i, 0001.f, (float)(scopeSize - 1)) * width,
            juce::jmap (scopeData[i], 0.0f, 1.0f, (float) height, 0.0f),
            juce::mapFromLog10((float) (i + 1), 0001.f, (float)(scopeSize - 1)) * width,
            juce::jmap (scopeData[i + 1], 0.0f, 1.0f, (float) height, 0.0f) });
    }
}

void FFTSpectrum::resized() { /*TODO*/ }

void FFTSpectrum::timerCallback() {
    if (processorRef.isNextFFTBlockReady()) {
        processorRef.processFFTData();

        auto minDB = -100.f;
        auto maxDB = 0.f;

        for (int i = 0; i < scopeSize; ++i) {
            auto skewedProportionX = 1.f - std::exp(std::log(1.f - (float) i / (float) scopeSize) * 0.2f);
            auto fftDataIndex = juce::jlimit(0, (int)fftSize / 2, (int)(skewedProportionX * (float) fftSize * 0.5f));
            auto level = juce::jmap(
                juce::jlimit(
                    minDB, maxDB,
                    juce::Decibels::gainToDecibels(processorRef.getFFTData(fftDataIndex)) - juce::Decibels::gainToDecibels((float) fftSize)
                ),
                minDB, maxDB, 0.f, 1.f
            );

            scopeData[i] = level;
        }

        processorRef.nextFFTBlockReadyReset();
        repaint();
    }
}