cmake_minimum_required(VERSION 3.15)
project(POWDER VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(JUCE)

juce_add_plugin(Powder
  COMPANY_NAME "Tauri-Invictus"
  IS_SYNTH FALSE
  IS_MIDI_EFFECT FALSE
  COPY_PLUGIN_AFTER_BUILD TRUE
  VST3_COPY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin"
  PLUGIN_MANUFACTURER_CODE "De4d"
  PLUGIN_CODE "P0wd"
  FORMATS VST3 Standalone
  PRODUCT_NAME "Powder Spectrum Analyzer"
)

juce_generate_juce_header(Powder)

target_sources(Powder
  PRIVATE
    PluginEditor.cpp
    PluginProcessor.cpp
    FFTComponent.cpp
)

target_compile_definitions(Powder
  PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
)

target_link_libraries(Powder
  PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
  PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)
