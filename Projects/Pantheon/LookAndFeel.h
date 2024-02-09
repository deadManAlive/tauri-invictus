#pragma once

#include <JuceHeader.h>

class PanLook : public LookAndFeel_V4 {
public:
    enum class Type {
        Gain,
        Pan,
    };

    PanLook();
    explicit PanLook(Type type);
    void drawRotarySlider(Graphics&, int, int, int, int, float, float, float, Slider&) override;
private:
    Colour leftColour = Colours::goldenrod;
    Colour rightColour = Colours::indianred;
    Colour thumbColour = Colours::bisque;
    Type type;
};