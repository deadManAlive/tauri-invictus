#pragma once

#include <JuceHeader.h>

class PanLook : public LookAndFeel_V4 {
public:
    enum class RotaryType {
        FromMin,
        FromMid,
    };

    enum class LinearType {
        Left,
        Right,
    };

    PanLook() = delete;
    PanLook(RotaryType rt, bool = false);
    PanLook(RotaryType, LinearType, bool = false);

    void drawRotarySlider(Graphics&, int, int, int, int, float, float, float, Slider&) override;
    void drawLinearSlider(Graphics&, int, int, int, int, float, float, float, Slider::SliderStyle, Slider&) override;
private:
    Colour leftColour = Colours::goldenrod;
    Colour rightColour = Colours::indianred;
    Colour thumbColour = Colours::bisque;
    RotaryType rotaryType;
    LinearType linearType;
    bool isReversed;
};