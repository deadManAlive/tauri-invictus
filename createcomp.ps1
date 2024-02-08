param (
    [Parameter(Mandatory=$true)]
    [string]$Name
)

$validId = '^[a-zA-Z_][a-zA-Z0-9_]*$'

if (-not ($Name -match $validId)) {
    Write-Error "'$Name' is not a C++ valid identifier!"
    exit 1
}

@"
#pragma once

#include <JuceHeader.h>

#include "PluginProcessor.h"

class $Name : public juce::Component
{
public:
    $Name(AudioPluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~$Name() override;
    void paint(juce::Graphics& g) override;
    void resized() override;
private:
    AudioPluginAudioProcessor& processorRef;
    AudioProcessorValueTreeState& parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ($Name)
};
"@ | Out-File -FilePath "$Name.h" -Encoding utf8

@"
#include "$Name.h"

$Name::$Name(AudioPluginAudioProcessor& p, AudioProcessorValueTreeState& apvts)
    : processorRef(p)
    , parameters(apvts) {}

$Name::~$Name() {}

void $Name::paint(juce::Graphics& g) {
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void $Name::resized() {}
"@ | Out-File -FilePath "$Name.cpp" -Encoding utf8

Write-Host "Done creating component '$Name'."