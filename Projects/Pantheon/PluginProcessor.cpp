#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <memory>

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
    , apvts(*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    InputGain.reset(sampleRate, 0.5 / sampleRate);
    
    juce::ignoreUnused (samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    // auto sampleNum = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    auto mg = apvts.getRawParameterValue("inputGain")->load();
    InputGain.setTargetValue(mg);

    buffer.applyGain(InputGain.getNextValue());
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this, apvts);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    ignoreUnused(destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ignoreUnused(data, sizeInBytes);
}

AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParameterLayout() {
    AudioProcessorValueTreeState::ParameterLayout parameterLayout;

    // INPUT GAIN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "inputGain",
            "Input Gain",
            NormalisableRange<float>{0.f, 2.f, 0.01f},
            1.f
        )
    );

    // INPUT PAN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "inputPan",
            "Input Gain",
            NormalisableRange<float>{-1.f, 1.f, 0.01f},
            0.f
        )
    );

    //TODO: this
    /**
    // LEFT PRE-GAIN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "leftPreGain",
            "Left Pre Gain",
            NormalisableRange<float>{-2.f, 2.f},
            1.f
        )
    );
    
    // RIGHT PRE-GAIN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "rightPreGain",
            "Right Pre Gain",
            NormalisableRange<float>{-2.f, 2.f},
            1.f
        )
    );

    // LEFT-TO-RIGHT GAIN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "leftToRightGain",
            "Left-to-Right Gain",
            NormalisableRange<float>{-2.f, 2.f},
            0.f
        )
    );

    // RIGHT-TO-LEFT GAIN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "righToLeftGain",
            "Right-to-Left Gain",
            NormalisableRange<float>{-2.f, 2.f},
            0.f
        )
    );

    // LEFT PAN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "leftPan",
            "Left Pan",
            NormalisableRange<float>{-1.f, 1.f},
            -1.f
        )
    );

    // RIGHT PAN
    parameterLayout.add(
        std::make_unique<AudioParameterFloat>(
            "rightPan",
            "Right Pan",
            NormalisableRange<float>{-1.f, 1.f},
            1.f
        )
    );
    */
    
    return parameterLayout;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}